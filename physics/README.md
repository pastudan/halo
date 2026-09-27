# Legacy physics entry

Player movement and collision now live in [`../engine/`](../engine/).

`build.sh` here simply invokes `engine/build.sh`. The old monolithic
`halo_phys.c` is retained as historical reference until Track A RE fully
supersedes the scaffolded `engine/` bodies; do not add new features here.
