#!/usr/bin/env bash

# Remove -lbsd from minilibx test template (not available on all Debian/Ubuntu systems)
if [ -f minilibx-linux/test/makefile.mk ]; then
    sed -i 's/-lbsd//g' minilibx-linux/test/makefile.mk
fi

# detects it's in nixos by checking for /nix/store
if [ -d "/nix/store" ] && [ -f minilibx-linux/configure ]; then
    echo "Patching minilibx configure for NixOS..."

    CACHE=".nix_inc_paths"

    # use cached paths if available
    if [ -f "$CACHE" ]; then
        source "$CACHE"
    else
        X11_INC=$(find /nix/store -path "*/include/X11/Xlib.h" 2>/dev/null | head -1 | sed 's|/X11/Xlib.h||')
        XPROTO_INC=$(find /nix/store -path "*/include/X11/X.h" 2>/dev/null | head -1 | sed 's|/X11/X.h||')
        XEXT_INC=$(find /nix/store -path "*/include/X11/extensions/XShm.h" 2>/dev/null | head -1 | sed 's|/X11/extensions/XShm.h||')
        echo "X11_INC=$X11_INC" > "$CACHE"
        echo "XPROTO_INC=$XPROTO_INC" >> "$CACHE"
        echo "XEXT_INC=$XEXT_INC" >> "$CACHE"
    fi

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
        # use old c standard where () means any args, not no args
        sed -i "s|-O3|-O3 -std=gnu89|g" minilibx-linux/Makefile.mk
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
