{ pkgs ? import <nixpkgs> { } }:

pkgs.mkShell {
  packages = with pkgs; [ SDL2 pkg-config gnumake gcc ];
}
