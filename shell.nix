# The Nix Shell support was added by Oto Brglez.
# If you have additional questions or need support, please reach out.
# - @otobrglez

with (import <nixpkgs> {});

mkShell {
  buildInputs = [
    scala-cli
    curl
    curlFull
    curlFull.dev
    zlib
  ];

  shellHook = ''

  '';
}
