#!/usr/bin/env python3
from distutils.core import setup

setup(name='cgull',
      version='0.1.1',
      description='Embedded code testing utility',
      author='Louis Simons',
      author_email='lousimons@gmail.com',
      packages=['cgull'],
      package_data={'cgull': ['unity/*']},
      include_package_data=True,
      entry_points={
        'console_scripts': ['cgull=cgull.cgull:main']
      },
      install_requires=[
        'toml'
      ])
