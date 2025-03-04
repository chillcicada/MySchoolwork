# list all recipes
default:
  @just --list

# format all nix files
nixfmt:
  nixpkgs-fmt .

# update nix flake.lock
nixup:
  nix flake update --commit-lock-file

# run nix flake checks
nixtest:
  nix flake check .

# clean all build artifacts
clean:
  ruff clean # python
