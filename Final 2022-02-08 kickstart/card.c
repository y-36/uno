#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>
#include "card.h"

struct s_card {
    unsigned int num;
    color_t color;
    type_t type;
};

static bool invrep(card_t c) {
    // Invariante de representación
    bool valid=false;
    valid = c != NULL;
    /*[COMPLETARDI]
     * Mejorar la invariante chequeando más
     * propiedades de los campos de la estructura
     */
    valid = valid && (/*c->num >= 0 &&*/ c->num <= 9);
    valid = valid && (c->color == red || c->color == green || c->color == blue || c->color == yellow);
    valid = valid && (c->type == normal || c->type == change_color || c->type == skip);
    return valid;
}

card_t card_new(unsigned int num, color_t color, type_t s) {
    card_t card=NULL;
    /*[COMPLETADO]*/
    card = malloc(sizeof(struct s_card));
    if (card != NULL) {
        card->num = num;
        card->color = color;
        card->type = s;
        assert(invrep(card));
    }
    return card;
}


type_t card_get_number(card_t card) {
    assert(invrep(card));
    return card->num;
}

color_t card_get_color(card_t card) {
    assert(invrep(card));
    return card->color;
}

type_t card_get_type(card_t card) {
    assert(invrep(card));
    return card->type;
}

bool card_samecolor(card_t c1, card_t c2) {
    /* [COMPLETARDO] */
    assert(invrep(c1) && invrep(c2));
    return c1-> color == c2->color;
}


bool card_samenum(card_t c1, card_t c2) {
    /* [COMPLETADO] */
    assert(invrep(c1) && invrep(c2));
    return c1->num == c2->num;   
}

bool card_compatible(card_t new_card, card_t pile_card) {
    bool compatible=false;
    assert(invrep(new_card) && invrep(pile_card));
    /*[COMPLETADO]*/
    if (new_card->type == change_color || new_card->color == pile_card->color || new_card->num == pile_card->num || (new_card->type == skip && pile_card->type == skip)) {
        compatible = true;
    }
    return compatible;
}

card_t
card_destroy(card_t card) {
    /*[COMPLETADO]*/
    assert(invrep(card));
    free(card);
    return NULL;

}



