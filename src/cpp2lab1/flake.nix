# This flake was initially generated by fh, the CLI for FlakeHub (version 0.1.17)
{
  # A helpful description of your flake
  description = "qt lab1";

  # Flake inputs
  inputs = {
    flake-compat.url = "https://flakehub.com/f/edolstra/flake-compat/*";

    flake-schemas.url = "https://flakehub.com/f/DeterminateSystems/flake-schemas/*";

    nixpkgs.url = "https://flakehub.com/f/NixOS/nixpkgs/0.1.*";
  };

  # Flake outputs that other flakes can use
  outputs = { self, flake-compat, flake-schemas, nixpkgs }:
    let
      # Helpers for producing system-specific outputs
      supportedSystems = [ "x86_64-linux" ];
      forEachSupportedSystem = f: nixpkgs.lib.genAttrs supportedSystems (system: f {
        pkgs = import nixpkgs { inherit system; };
      });
    in
    {
      # Schemas tell Nix about the structure of your flake's outputs
      schemas = flake-schemas.schemas;

      # Development environments
      devShells = forEachSupportedSystem ({ pkgs }: {
        default = pkgs.mkShell {
          # Pinned packages available in the environment
          packages = with pkgs; [
            curl
            git
            jq
            wget
            nixpkgs-fmt

            xmake
            just
            llvm_18
            valgrind
            qt6.full
            qtcreator
          ];
        };
      });
    };
}