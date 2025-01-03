nixfmt:
  nixpkgs-fmt .

nixup:
  nix flake update --commit-lock-file

nixtest:
  nix flake check .

clean:
  ruff clean
  pnpm clean
