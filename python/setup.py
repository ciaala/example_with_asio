"""
Cevelop style
"""
from setuptools import setup

setup(
    name='cevelop',
    version='1.0.0',
    description='The cevelop color style',
    long_description='',
    url='https://github.com/IFS-HSR/cevelop-pygments',
    author='Felix Morgner',
    install_requires=['Pygments'],
    packages=['cevelop'],
    entry_points={
        'pygments.styles': [
            'cevelop = cevelop:CevelopStyle'
        ]
    },
)
