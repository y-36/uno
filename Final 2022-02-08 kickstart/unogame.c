#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "unogame.h"
#include "card.h"

#define NO_PLAYER -1

struct s_ugame {
    /*[COMPLETADO]*/
    card_t *pile;
    unsigned int pile_size;
    color_t current_color;
    player_t next_player;
};

static bool invrep(unogame_t uno) {
    bool valid = uno != NULL;
    valid = valid && uno->pile != NULL;
    valid = valid && uno->pile_size > 0;
    valid = valid && (uno->next_player >= 0 && uno->next_player < NUM_PLAYERS);
    return valid;
}

unogame_t
uno_newgame(card_t card) {
    /*[COMPLETADO] */
    unogame_t new_game = malloc(sizeof(struct s_ugame));
    if (new_game != NULL) {
        new_game->pile = malloc(sizeof(card_t));
        if (new_game->pile != NULL) {
            new_game->pile[0] = card;
            new_game->pile_size = 1;
            new_game->current_color = card_get_color(card);
            new_game->next_player = 0;
            assert(invrep(new_game));
        } else {
            free(new_game);
            new_game = NULL;
        }
    }
    return new_game;
}

card_t uno_topcard(unogame_t uno) {
    /*[COMPLETADO]*/
    assert(invrep(uno));
    return uno->pile[uno->pile_size - 1];
}

unogame_t uno_addcard(unogame_t uno, card_t c) {
    /*[COMPLETADO]*/
    assert(invrep(uno));
    uno->pile = realloc(uno->pile, (uno->pile_size + 1) * sizeof(card_t));
    if (uno->pile != NULL) {
        uno->pile[uno->pile_size] = c;
        uno->pile_size++;
        uno->current_color = card_get_color(c);
        uno->next_player = (uno->next_player + 1) % NUM_PLAYERS;
        assert(invrep(uno));
    }
    return uno;
}

unsigned int uno_count(unogame_t uno) {
    /*[COMPLETARDO] */
    assert(invrep(uno));
    return uno->pile_size;
}

bool uno_validpile(unogame_t uno) {
    /*[COMPLETAR] */
    assert(invrep(uno));
    for (unsigned int i = 0; i < uno->pile_size; i++) {
        if (!invrep(uno)) {
            return false;
        }
    }
    return true;
}

color_t uno_currentcolor(unogame_t uno) {
    /*[COMPLETADO]*/
    assert(invrep(uno));
    return uno->current_color;
}

player_t uno_nextplayer(unogame_t uno) {
    /*[COMPLETADO]*/
    assert(invrep(uno));
    return uno->next_player;
}



card_t * uno_pile_to_array(unogame_t uno) {
    /*[COMPLETAR]*/
    assert(invrep(uno));
    card_t *array = malloc(uno->pile_size * sizeof(card_t));
    if (array != NULL) {
        for (unsigned int i = 0; i < uno->pile_size; i++) {
            array[i] = uno->pile[i];
        }
    }
    return array;
}

unogame_t
uno_destroy(unogame_t uno) {
    /*[COMPLETADO]*/
    assert(invrep(uno));
    for (unsigned int i = 0; i < uno->pile_size; i++) {
        card_destroy(uno->pile[i]);
    }
    free(uno->pile);
    free(uno);
    return NULL;
}

