{
  description = "flake for cc's schoolwork";

  inputs = {
    nixpkgs.url = "github:Nixos/nixpkgs/nixos-unstable";
  };

  outputs =
    { nixpkgs, ... }:
    let
      supportedSystems = [ "x86_64-linux" ];
      forEachSupportedSystem =
        f: nixpkgs.lib.genAttrs supportedSystems (system: f { pkgs = import nixpkgs { inherit system; }; });
    in
    {
      devShells = forEachSupportedSystem (
        { pkgs }:
        {
          # use `nix develop .#<name> -c zsh` to enter the difference shell
          cpp = pkgs.mkShell {
            packages = with pkgs; [
              doxygen
              libclang
              valgrind
              qt6.full
            ];
          };

          fortran = pkgs.mkShell {
            packages = with pkgs; [
              mpi
              llvmPackages.openmp

              gfortran
              fprettify
            ];
          };

          ml = pkgs.mkShell {
            packages = with pkgs; [
              parallel # parallelize shell commands
              imagemagick # image manipulation

              cairo # required by anylabeling
              openssl # required by requests
            ];

            shellHook = ''
              export LD_LIBRARY_PATH=$NIX_LD_LIBRARY_PATH:$LD_LIBRARY_PATH
            '';
          };

          misc = pkgs.mkShell {
            packages = with pkgs; [
              ovito # visualizing crystal structures
              quarto # convert jupyter notebooks to pdf
            ];

            shellHook = ''
              export LD_LIBRARY_PATH=$NIX_LD_LIBRARY_PATH:$LD_LIBRARY_PATH
            '';
          };

          fmt = pkgs.mkShell {
            packages = with pkgs; [
              ruff
              typstyle
              fprettify
              clang-tools
            ];
          };

          bayes = pkgs.mkShell {
            buildInputs = with pkgs; [ graphviz ];
          };
        }
      );
    };
}
