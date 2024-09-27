nixfmt:
  nixpkgs-fmt .

nixup:
  nix flake update --commit-lock-file

nixtest:
  nix flake check .
