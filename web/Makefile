# Build cub3D for the browser against the SDL2 MiniLibX shim.
# Run from the repo root:  make -C web wasm   (needs emcc on PATH)
#                          make -C web serve  (after wasm)

.DEFAULT_GOAL := wasm
.PHONY: wasm serve clean fclean re

WASM_OBJ_DIR = obj/wasm
WASM_OUT = dist/index.html

GAME_SRCS = $(foreach d,../src ../src/input ../src/render ../src/parsing,$(wildcard $(d)/*.c))
LIBFT_SRCS = $(wildcard ../libft/*.c)
SHIM_SRCS = ../mlx_sdl/mlx_sdl.c

WASM_OBJS = $(patsubst ../%.c,$(WASM_OBJ_DIR)/%.o,$(GAME_SRCS) $(LIBFT_SRCS) $(SHIM_SRCS))

ASSETS = $(wildcard ../maps/*.cub) $(wildcard ../textures/XPMs/*.xpm)

# mlx_sdl comes first so that "mlx.h" resolves to the shim
INC = -I ../mlx_sdl -I ../include -I ../libft

DEPFLAGS = -MMD -MP

EMCC = emcc
EMCC_CFLAGS = -Wall -Wextra -Werror -std=c2y -O2 -sUSE_SDL=2
EMCC_LDFLAGS = -O2 -sUSE_SDL=2 -sALLOW_MEMORY_GROWTH=1 \
	--preload-file ../maps@/maps \
	--preload-file ../textures/XPMs@/textures/XPMs \
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
