{ pkgs ? import <nixpkgs> { } }:

pkgs.mkShell {
  packages = with pkgs; [ sdl3 pkg-config gnumake gcc ];
}
