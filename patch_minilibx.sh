#!/usr/bin/env bash
# detects it's in nixos by checking for /nix/store
if [ -d "/nix/store" ] && [ -f minilibx-linux/configure ]; then
    echo "Patching minilibx configure for NixOS..."

    # find all required X11 include paths
    X11_INC=$(find /nix/store -path "*/include/X11/Xlib.h" 2>/dev/null | head -1 | sed 's|/X11/Xlib.h||')
    XPROTO_INC=$(find /nix/store -path "*/include/X11/X.h" 2>/dev/null | head -1 | sed 's|/X11/X.h||')
    XEXT_INC=$(find /nix/store -path "*/include/X11/extensions/XShm.h" 2>/dev/null | head -1 | sed 's|/X11/extensions/XShm.h||')

    # combine include paths
    ALL_INC="$X11_INC -I$XPROTO_INC -I$XEXT_INC"

    echo "Using X11 include paths: $ALL_INC"

    cat > minilibx-linux/makefile.gen << EOF
INC=$ALL_INC
HT==
DOCP=no
OLIBA=
INCLIB=
FLAG_GL=-lGL
EOF

    if [ -f minilibx-linux/Makefile.mk ]; then
        sed -i "s|INC.*=.*%%%%|include makefile.gen|g" minilibx-linux/Makefile.mk
    fi

    cat > minilibx-linux/configure << 'EOF'
#!/usr/bin/env bash
echo "Using pre-generated configuration for NixOS"
exit 0
EOF
    chmod +x minilibx-linux/configure

    cat > minilibx-linux/Makefile << 'EOF'
all:
	@./configure
	@make -f Makefile.mk all

clean:
	@make -f Makefile.mk clean

re: clean all
EOF
fi
