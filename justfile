# list all recipes
default:
  @just --list

# update nix flake.lock
nixup:
  nix flake update --commit-lock-file

# run nix flake checks
nixtest:
  nix flake check .

# clean all build artifacts
clean:
  ruff clean # python
