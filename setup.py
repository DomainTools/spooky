from distutils.core import setup, Extension

setup(name = 'spooky',
    version = '2.0.0',
    license = 'MIT License',
    description = 'Wrapper for SpookyHash V2',
    long_description = open('README.md').read(),
    author = 'Derek Wilson',
    author_email = 'dwilson@domaintools.com',
    url = 'https://github.com/DomainTools/spooky',
    ext_modules = [
        Extension('spooky', sources = ['spookymodule.cpp', 'SpookyV2.cpp'])],
    keywords = "jenkins spooky hash v2 checksum noncryptographic",
    classifiers = [
        'Development Status :: 5 - Production/Stable',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Topic :: Software Development']
)
