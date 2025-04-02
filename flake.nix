{
  description = "flake for cc's schoolwork";

  inputs = {
    nixpkgs.url = "github:Nixos/nixpkgs/nixos-unstable";
  };

  outputs =
    {
      nixpkgs,
      ...
    }:
    let
      supportedSystems = [
        "x86_64-linux"
        "aarch64-darwin"
        "x86_64-darwin"
        "aarch64-linux"
      ];
      forEachSupportedSystem =
        f:
        nixpkgs.lib.genAttrs supportedSystems (
          system:
          f {
            pkgs = import nixpkgs {
              inherit system;
            };
          }
        );
    in
    {
      devShells = forEachSupportedSystem (
        { pkgs }:
        {
          default = pkgs.mkShell {
            packages = with pkgs; [
              quarto

              ovito

              mpi
              valgrind
              doxygen
              qt6.full

              parallel # parallelize shell commands
              imagemagick # image manipulation

              cairo # required by anylabeling
              openssl # required by requests

              pkg-config # pkg-config, required by rust
            ];
          };
        }
      );
    };
}
