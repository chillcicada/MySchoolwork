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
              ovito # visualizing crystal structures
              quarto # convert jupyter notebooks to pdf

              mpi
              llvmPackages.openmp

              doxygen
              gfortran
              valgrind
              qt6.full
              fprettify

              parallel # parallelize shell commands
              imagemagick # image manipulation

              cairo # required by anylabeling
              openssl # required by requests

              pkg-config # pkg-config, required by rust
            ];

            shellHook = ''
              export LD_LIBRARY_PATH=$NIX_LD_LIBRARY_PATH:$LD_LIBRARY_PATH
            '';
          };
        }
      );
    };
}
