/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekibar <ekibar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:11:06 by ekibar            #+#    #+#             */
/*   Updated: 2025/11/10 22:22:50 by ekibar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	create_window(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		exit_safe(game, "Mlx_init failed!", 1);
	load_textures(game, game->map.north_texture_path, 0);
    load_textures(game, game->map.south_texture_path, 1);
    load_textures(game, game->map.west_texture_path, 2);
    load_textures(game, game->map.east_texture_path, 3);
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, WIN_W, WIN_H,
			"cub3D");
	if (!game->mlx.win_ptr)
		exit_safe(game, "Failed to create window!", 1);
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr, WIN_W, WIN_H);
	if (!game->mlx.img_ptr)
		exit_safe(game, "Failed to create image!", 1);
	game->mlx.addr = mlx_get_data_addr(game->mlx.img_ptr, &game->mlx.bpp,
			&game->mlx.line_len, &game->mlx.endian);
	if (!game->mlx.addr)
		exit_safe(game, "Failed to get image data address\n", 1);
	hooks_handler(game);
	mlx_loop(game->mlx.mlx_ptr);
}
/*

Little-endian
En az anlamlı bayt (LSB) önce, en anlamlı bayt (MSB) sonra saklanır.
Bellekte düşük adreslerde LSB, yüksek adreslerde MSB bulunur.
Yaygın: x86 ve x86_64 (Intel/AMD) mimarileri little-endian kullanır.

Big-endian
En anlamlı bayt (MSB) önce, en az anlamlı bayt (LSB) sonra saklanır.
Bellekte düşük adreslerde MSB, yüksek adreslerde LSB bulunur.
Eskiden bazı CPU'larda (ör. Motorola 68k, bazı ağ protokolleri) yaygın.
Görsel örnek
Düşün: 32-bit hex değerimiz = 0x12345678

Big-endian bellekte (adres artışı aşağı yönünde):
[adres] -> 0x12 0x34 0x56 0x78
(düşük adres: 0x12, yüksek adres: 0x78)

Little-endian bellekte:
[adres] -> 0x78 0x56 0x34 0x12
(düşük adres: 0x78, yüksek adres: 0x12)

Yani aynı 4 byte bellekte ters sırada görünür.

*/