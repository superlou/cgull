#!/usr/bin/env python3
from distutils.core import setup

setup(name='cgull',
      version='0.1.0',
      description='Embedded code testing utility',
      author='Louis Simons',
      author_email='lousimons@gmail.com',
      packages=['cgull'],
      entry_points={
        'console_scripts': ['cgull=cgull.cgull:main']
      },
      install_requires=[
        'toml'
      ])
