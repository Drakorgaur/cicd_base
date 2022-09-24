# CI/CD for VUT FIT projects that is based on C language

*authored by Mark Barzali -- [@Drakorgaur](github.com/Drakorgaur)*

## Introduction

Project is created to simplify CI/CD process for VUT FIT projects that are based on C language.
This helps to:
- lint code
- run unit tests if they are present
- build project
- run end-to-end tests if they are present
- pack the project into a `tar.gz` archive

## Pre-requisites
This CI/CD are based mostly on your **Makefile**(see [this section](#makefile)), as all our projects can be different.
There are some files/directories your repo must have:
- Makefile
- folder with your source code
- folder with your unit tests (optional)
- your binary name

## Usage
To start using this project, you need to add two files to your project:
- `.github/workflows/on_pr.yml`
- `.github/workflows/on_merge.yml`

*Note: you should create folders `.guthub` in your project root directory and `workflows` inside it*


`on_pr.yml` will run linter and unit tests if you have changes(on your branch) in your source code or unit tests.  
`on_merge.yml` build, end-to-end tests and pack your project using `make pack`.

This files using variables `src`, `unit_tests`, `makefile` and `binary`

| Variable   | Description                  | Example    |
|------------|------------------------------|------------|
| src        | folder with your source code | ./src      |
| unit_tests | folder with your unit tests  | ./tests    |
| makefile   | path to your Makefile        | ./Makefile |
| binary     | your binary name             | ifg_bin    |


___
`on_pr.yml`:
```yaml
on:
  workflow_dispatch:
  pull_request:

jobs:
  flow:
    uses: Drakorgaur/cicd_base/.github/workflows/pull_request.yml
    with:
      src: ./src
      unit_tests: true
      makefile: ./Makefile
```
___
`on_merge.yml`:
```yaml
on:
  workflow_dispatch:
  push:
    branches:
      - 'master'

jobs:
  flow:
    uses: Drakorgaur/cicd_base/.github/workflows/merge_master.yml
    with:
      makefile: ./Makefile
      binary: 'compile'
```

*Good practice to protect your `master` branch from direct commits and force pushes. See [how to protect master](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/defining-the-mergeability-of-pull-requests/managing-a-branch-protection-rule).*



## Makefile
your make file should be able to:
- build your project
- run unit tests (if present)
- pack your project into a `tar.gz` archive

Makefile:
```makefile
# directory mapping
PROJ_D=$(shell pwd)
SRC_D=src
BIN_D=bin

# compiler config
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99
# packing config
TAR_NAME=project

test:
    # run your unit tests (will be updated in the future)
	echo "Testing here"

compile:
	mkdir -p $(BIN_D)
	$(CC) $(CFLAGS) $(wildcard $(PROJ_D)/$(SRC_D)/*.c) -o $(BIN_D)/$@

pack:
	tar -czvf $(TAR_NAME).tar.gz $(SRC_D) $(BIN_D) README.md

clean:
	rm $(PROJ_D)/$(BIN_D)/*
	rm -f $(PROJ_D)/$(TAR_NAME).tar.gz
```