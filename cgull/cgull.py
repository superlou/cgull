#!/usr/bin/python3
import subprocess
import toml
import os
from os import path
import argparse


def remove_old_executable(name):
    if os.name == 'nt':
        name += '.exe'

    if path.exists(name):
        os.remove(name)


def build(target, settings, src, inc, flags=None):
    test_name = 'test_' + target
    output_name = path.join('build', test_name)
    os.makedirs('build', exist_ok=True)
    remove_old_executable(output_name)

    unity_path = path.join(path.dirname(path.abspath(__file__)), 'unity')

    cmd = ['gcc']

    if flags:
        cmd += flags

    cmd += ['-I.']
    cmd += ['-I' + unity_path]
    cmd += ['-I./helpers']
    cmd += ['-I', inc]
    cmd += [path.join(unity_path, 'unity.c')]

    if 'helpers' in settings:
        cmd += [path.join('helpers', filename) for filename in settings['helpers']]

    cmd += [path.join('tests', test_name + '.c')]
    cmd += [path.join(src, filename) for filename in settings['depends']]
    cmd += ['-o', output_name]

    subprocess.check_call(cmd)


def run(target):
    executable = './build/test_' + target

    if os.name == 'nt':
        executable += '.exe'

    try:
        subprocess.run([executable])
    except Exception as e:
        print(f'Failed to run {executable}: {e}')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-m', '--module', nargs='+', help="Test module to run")
    args = parser.parse_args()

    config = toml.load(open('config.toml'))

    for target, settings in config['test'].items():
        if args.module and target not in args.module:
            continue

        build(target, settings,
              config['target_src'], config['target_inc'],
              config.get('gcc_flags', None))
        run(target)


if __name__ == '__main__':
    main()
