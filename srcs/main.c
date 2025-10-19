#include "../lib/minilibx-linux/mlx.h"
#include <stdlib.h> // exit için
#include <stdio.h>  // printf için (hata durumunda)

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// MLX bağlantılarını bir arada tutmak için basit bir struct
typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_game;

/*
 * Bu fonksiyon, pencerenin 'X' tuşuna (DestroyNotify olayı)
 * basıldığında tetiklenir.
 */
int	close_window_hook(t_game *game)
{
	printf("Pencere kapatılıyor...\n");
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	// MLX'in bazı versiyonlarında destroy'dan sonra free gerekir
	// mlx_destroy_display(game->mlx_ptr);
	// free(game->mlx_ptr);
	exit(0); // Programı temizce sonlandır
	return (0);
}

int	main(void)
{
	t_game	game;

	// 1. MLX bağlantısını başlat
	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
	{
		printf("MLX bağlantısı kurulamadı!\n");
		return (1);
	}

	// 2. Yeni bir pencere oluştur
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D Test Penceresi");
	if (!game.win_ptr)
	{
		printf("Pencere oluşturulamadı!\n");
		return (1);
	}

	// 3. Olayları dinlemeye başla
	// Kapatma tuşuna basıldığında (event 17) 'close_window_hook'u çağır
	mlx_hook(game.win_ptr, 17, 0, close_window_hook, &game);

	// 4. MLX döngüsünü başlat (program burada kilitlenir ve olayları bekler)
	printf("Pencere açıldı. Kapatmak için 'X' tuşuna basın.\n");
	mlx_loop(game.mlx_ptr);
	return (0);
}