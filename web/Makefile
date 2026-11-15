# Build cub3D for the browser on top of the gfx layer (SDL3).
# Run from the repo root:  make -C web wasm   (needs emcc on PATH)
#                          make -C web serve  (after wasm)

.DEFAULT_GOAL := wasm
.PHONY: wasm serve clean fclean re

WASM_OBJ_DIR = obj/wasm
WASM_OUT = dist/index.html

GAME_SRCS = $(foreach d,../src ../src/input ../src/render ../src/parsing,$(wildcard $(d)/*.c))
LIBFT_SRCS = $(wildcard ../libft/*.c)
GFX_SRCS = ../gfx/gfx.c

WASM_OBJS = $(patsubst ../%.c,$(WASM_OBJ_DIR)/%.o,$(GAME_SRCS) $(LIBFT_SRCS) $(GFX_SRCS))

ASSETS = $(wildcard ../maps/*.cub) $(wildcard ../textures/*.bmp)

INC = -I ../gfx -I ../include -I ../libft

DEPFLAGS = -MMD -MP

EMCC = emcc
EMCC_CFLAGS = -Wall -Wextra -Werror -std=c2y -O2 -sUSE_SDL=3 -Wno-experimental
EMCC_LDFLAGS = -O2 -sUSE_SDL=3 -Wno-experimental -sALLOW_MEMORY_GROWTH=1 \
	--preload-file ../maps@/maps \
	--preload-file ../textures@/textures \
	--shell-file shell.html -lm

wasm: $(WASM_OUT)

$(WASM_OUT): $(WASM_OBJS) shell.html $(ASSETS)
	@mkdir -p dist
	$(EMCC) $(WASM_OBJS) -o $@ $(EMCC_LDFLAGS)

$(WASM_OBJ_DIR)/%.o: ../%.c
	@mkdir -p $(dir $@)
	$(EMCC) $(EMCC_CFLAGS) $(DEPFLAGS) $(INC) -c $< -o $@

serve:
	cd dist && python3 -m http.server 8000

-include $(WASM_OBJS:.o=.d)

clean:
	rm -rf obj

fclean: clean
	rm -rf dist

re: fclean wasm
