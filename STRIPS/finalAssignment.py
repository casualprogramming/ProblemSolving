#!/usr/bin/env python
"""
Example of using PyDDL to solve the "Missionaries and Cannibals" Problem.
A boat must transport a group of 3 missionaries and 3 cannibals across a river,
but at no time can the cannibals outnumber the missionaries at either side of
the river.
"""
from __future__ import print_function
from pyddl import Domain, Problem, Action, neg, planner

def problem(verbose):
    domain = Domain((
        
        #ready-for-battle & defencable -> enemy is defenced
        Action(
            'enemy-defenced',
            parameters=(
                ('state', '_state'),
                ('state', '_prev_state'),
            ),
            preconditions=(
                ('defencable','_state'),
                ('ready-for-battle',''),
                ('character_state', '_state'),
                ('character_prev_state', '_prev_state'),
            ),
            effects=(
                neg(('character_prev_state', '_prev_state')),
                neg(('character_state', '_state')),
                ('character_prev_state', '_state'),
                ('character_state', 'defenced'),
                ('use-defence',''),
            ),
        ),
        
        #ready-for-battle & exhaustable -> enemy is exhausted
        Action(
            'enemy-exhausted',
            parameters=(
                ('state', '_state'),
                ('state', '_prev_state'),
            ),
            preconditions=(
                ('exhaustable', '_state'),
                ('ready-for-battle',''),
                ('character_state', '_state'),
                ('character_prev_state', '_prev_state'),
            ),
            effects=(
                neg(('character_prev_state', '_prev_state')),
                neg(('character_state', '_state')),
                ('character_state', 'exhausted'),
                ('character_prev_state', '_state'),
            ),
        ),

        #ready-for-battle & ignitable -> enemy is ignited
        Action(
            'enemy-ignited',
            parameters=(
                ('state', '_state'),
                ('state', '_prev_state'),
            ),
            preconditions=(
                ('ignitable', '_state'),
                ('ready-for-battle',''),
                ('character_state', '_state'),
                ('character_prev_state', '_prev_state'),
            ),
            effects=(
                neg(('character_prev_state', '_prev_state')),
                neg(('character_state', '_state')),
                ('character_prev_state', '_state'),
                ('character_state', 'ignited'),
                ('use-ignite',''),
            ),
        ),

        # ready-for-battle & electric ready & electric shockable -> enemy is electric shocked
        Action(
            'electric-shock',
            parameters=(
                ('state', '_state'),
                ('state', '_prev_state'),
            ),
            preconditions=(
                ('electric-shockable','_state','_prev_state'),
                ('electric-ready',''),
                ('ready-for-battle',''),
                ('character_state', '_state'),
                ('character_prev_state', '_prev_state'),
            ),
            effects=(
                neg(('character_prev_state', '_prev_state')),
                neg(('character_state', '_state')),
                ('character_prev_state', '_state'),
                ('character_state', 'electric-shocked'),
            ),
        ),

        # ready-for-battle & electric preparable -> electric is prepared
        Action(
            'electric-ready-perfectly',
            parameters=(
                ('state', '_state'),
                ('state', '_prev_state'),
            ),
            preconditions=(
                ('electric-preparable','_state'),
                ('ready-for-battle',''),
                ('character_state', '_state'),
                ('character_prev_state', '_prev_state'),
            ),
            effects=(
                ('electric-ready',''),
            ),
        ),

        # idle -> ready for battle
        Action(
            'ready-for-battle',
            parameters=(
                ('state', '_state'),
                ('state', '_prev_state'),
            ),
            preconditions=(
                ('character_state','idle'),
                ('character_state','_state'),
                ('character_prev_state', '_prev_state'),
            ),
            effects=(
                ('ready-for-battle',''),
            ),
        ),
    ))
    problem = Problem(
        domain,
        {
            'state': ('electric-shocked', 'idle', 'defenced', 'ignited', 'exhausted', 'NONE'),
        },
        init=(

            ('electric-shockable','exhausted','defenced'),#defenced -> exghausted -> now it can use electric shock
            ('electric-shockable','exhausted','ignited'),#ignited -> exghausted -> now it can use electric shock

            ('electric-preparable','ignited'),#prepare electric when enemy was ignited
            ('electric-preparable','defenced'),#prepare electric when enemy was exhausted


            ('defencable','idle'),
            ('ignitable','idle'),
            ('exhaustable','ignited'),
            ('exhaustable','defenced'),
            
            ('character_state', 'idle'),
            ('character_prev_state', 'NONE'),
        ),
        goal=(
            ('character_state', 'electric-shocked'),
            
            # case 1 use ignite
            ('use-ignite',''),

            # 1. ready for battle
            # 2. ignite to enemy
            # 3. ready electric
            # 4. enemy was exhausted
            # 5. electric shock to enemy
            
            ################
            # case 2 use defence
            # ('use-defence',''),
            
            # 1. ready for battle
            # 2. enemy was defenced
            # 3. ready electric
            # 4. enemy was exhausted
            # 5. electric shock to enemy
            
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
