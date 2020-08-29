#!/usr/bin/env python
"""
공격/방어/회복 등의 action을 턴 방식으로 실행하고, me가 결국 enemy를 이기는 것을 goal로 하는 Plan
"""
from __future__ import print_function
from pyddl import Domain, Problem, Action, neg, planner


def problem(verbose):
    domain = Domain((
        # 일반 공격 : me와 enemy 모두 가능한 액션, 현재 턴(now_turn)인 공격자가 상대방(prev_turn)의 hp를 20 깎음
        Action(
            'normal-attack',
            parameters=(
                ('turn', 't'),
                ('turn', 'prev_t'),
            ),
            preconditions=(
                ('now_turn', 't'),
                ('prev_turn', 'prev_t'),
            ),
            effects=(
                neg(('now_turn', 't')),
                neg(('prev_turn', 'prev_t')),
                ('now_turn', 'prev_t'),
                ('prev_turn', 't'),
                ('+=', ('hp', 'prev_t'), -20),
                ('-=', ('damaged', 'prev_t'), ('damaged', 'prev_t')),
                ('+=', ('damaged', 'prev_t'), -20),
            ),
        ),
        # 마법 공격 : me와 enemy 모두 가능한 액션, 현재 턴(now_turn)인 공격자가 상대방(prev_turn)의 hp를 35 깎고, mp를 40 소모
        # mp가 40 이상일 때만 사용 가능
        Action(
            'magic-attack',
            parameters=(
                ('turn', 't'),
                ('turn', 'prev_t'),
            ),
            preconditions=(
                ('now_turn', 't'),
                ('prev_turn', 'prev_t'),
                ('>=', ('mp', 't'), 40),
            ),
            effects=(
                neg(('now_turn', 't')),
                neg(('prev_turn', 'prev_t')),
                ('now_turn', 'prev_t'),
                ('prev_turn', 't'),
                ('+=', ('hp', 'prev_t'), -35),
                ('+=', ('mp', 't'), -40),
                ('-=', ('damaged', 'prev_t'), ('damaged', 'prev_t')),
                ('+=', ('damaged', 'prev_t'), -35),
            ),
        ),
        # hp 회복 : me 만 사용 가능한 스킬, me의 mp를 60 소모하여, hp를 55 회복 함
        # mp가 60 이상일 때만 사용 가능, 현재 hp가 0 보다 클 때만 사용 가능(부활 불가)
        Action(
            'heal-me',
            preconditions=(
                ('now_turn', 'me'),
                ('prev_turn', 'enemy'),
                ('>', ('hp', 'me'), 0),
                ('>=', ('mp', 'me'), 60),
            ),
            effects=(
                neg(('now_turn', 'me')),
                neg(('prev_turn', 'enemy')),
                ('now_turn', 'enemy'),
                ('prev_turn', 'me'),
                ('+=', ('hp', 'me'), 55),
                ('+=', ('mp', 'me'), -60),
            ),
        ),
        # mp 회복 : me 만 사용 가능한 스킬, me의 mp를 40 회복 함
        Action(
            'charge-my-magicka',
            preconditions=(
                ('now_turn', 'me'),
                ('prev_turn', 'enemy'),
            ),
            effects=(
                neg(('now_turn', 'me')),
                neg(('prev_turn', 'enemy')),
                ('now_turn', 'enemy'),
                ('prev_turn', 'me'),
                ('+=', ('mp', 'me'), 40),
            ),
        ),
        # 반격 : me 만 사용 가능한 스킬, me의 mp를 60 소모하여, 바로 직전 턴에 enemy 에게 받은 데미지 만큼 hp를 회복함
        # mp가 60 이상일 때만 사용 가능, 직전 턴에 받은 데미지를 회복한 hp가 0 보다 커야만 사용 가능
        Action(
            'reflect-enemy-attack',
            preconditions=(
                ('now_turn', 'me'),
                ('prev_turn', 'enemy'),
                ('>', ('hp', 'me'), ('damaged', 'me')),
                ('>=', ('mp', 'me'), 60),
            ),
            effects=(
                neg(('now_turn', 'me')),
                neg(('prev_turn', 'enemy')),
                ('now_turn', 'enemy'),
                ('prev_turn', 'me'),
                ('-=', ('hp', 'me'), ('damaged', 'me')),
                ('+=', ('hp', 'enemy'), ('damaged', 'me')),
                ('+=', ('mp', 'me'), -60),
                ('-=', ('damaged', 'me'), ('damaged', 'me')),
            ),
        ),
    ))
    problem = Problem(
        domain,
        {
            'turn': ('me', 'enemy'),  # 가능한 turn Domain
        },
        # hp:100, mp:80 인 enemy와 hp:50, mp:100인 me 중 enemy의 선공으로 게임을 시작하는 초기 state
        init=(
            ('now_turn', 'enemy'),  # enemy 선공
            ('prev_turn', 'me'),  # prev_turn 이지만 init 단계이므로 다음 턴 공격자인 me
            ('=', ('hp', 'me'), 50),  # me의 시작 hp
            ('=', ('mp', 'me'), 100),  # me의 시작 mp
            ('=', ('damaged', 'me'), 0),  # me가 입은 데미지 초기 값, reflect-enemy-attack 액션을 통해 받은 데미지를 회복하기 위해 필요
            ('=', ('hp', 'enemy'), 100),  # enemy의 시작 hp
            ('=', ('mp', 'enemy'), 80),  # enemy의 시작 mp
            ('=', ('damaged', 'enemy'), 0),  # enemy가 입은 데미지 초기 값, enemy는 reflect-enemy-attack 액션을 사용할 수 없지만, domain parameter로 인한 런타임 에러를 막기위해 필요
        ),
        # goal test 직전인 마지막 액션의 turn이 me이고, 생존 상태의 me가 enemy를 쓰러트린 state
        # me가 생존한 상태에서, enemy를 쓰러트리는 state
        goal=(
            ('prev_turn', 'me'),
            ('>', ('hp', 'me'), 0),
            ('<=', ('hp', 'enemy'), 0),
        )
    )

    plan = planner(problem, verbose=verbose)
    if plan is None:
        print('No Plan!')
    else:
        for action in plan:
            print(action)

if __name__ == '__main__':
    from optparse import OptionParser
    parser = OptionParser(usage="Usage: %prog [options]")
    parser.add_option('-q', '--quiet',
                      action='store_false', dest='verbose', default=True,
                      help="don't print statistics to stdout")

    # Parse arguments
    opts, args = parser.parse_args()
    problem(opts.verbose)