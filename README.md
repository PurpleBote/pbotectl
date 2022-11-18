[![GitHub release](https://img.shields.io/github/release/PurpleBote/pbotectl.svg?label=latest%20release)](https://github.com/PurpleBote/pbotectl/releases/latest)
[![License](https://img.shields.io/github/license/PurpleBote/pbotectl.svg)](https://github.com/PurpleBote/pbotectl/blob/master/LICENSE)

# pbotectl

pbotectl (Purple Bote Control Tool) - is a CLI utility for [pboted](https://github.com/PurpleBote/pboted)

## Features

- Show some pboted entities and metrics (JSON and plain text)

### Planned Features

- Bote identity creation
- Aliases controling
- Launching periodic tasks
- Metrics and statuses

## Resources

* [Tickets/Issues](https://github.com/PurpleBote/pbotectl/issues)

## Installing

You can fetch precompiled packages and binaries on [release](https://github.com/PurpleBote/pbotectl/releases/latest) page.

### Supported systems

- GNU/Linux - [![Build](https://github.com/PurpleBote/pbotectl/actions/workflows/build.yml/badge.svg)](https://github.com/PurpleBote/pbotectl/actions/workflows/build.yml)
  - Debian / Ubuntu - [![Build DEB](https://github.com/PurpleBote/pbotectl/actions/workflows/build-deb.yml/badge.svg)](https://github.com/PurpleBote/pbotectl/actions/workflows/build-deb.yml)

## Building

- Install requirements:
    - Compiler with ANSI C89 support (GCC, Clang)
    - cmake >= 3.7
- Clone

```sh
git clone https://github.com/PurpleBote/pbotectl.git
cd pbotectl
git submodule update --init
```

- Build:

```bash
cd build
cmake .
make
```

## Usage

- **pboted** need to be run with enabled and configured control interface
- You can see available commands with `./pbotectl help`

## Donations

- **XMR**: `89xqER2GpS3Bqm8z8AuqKx5Cpf9BR1codN1VdufcAEbFP2t9oWPvKpzfr6s6dNDRFHVfRijiCQA3uCFYQLzfsWtM3ahbSqp`

## License

This project is licensed under the GPL-3.0 license, which can be found in the file LICENSE in the root of the project source code.
