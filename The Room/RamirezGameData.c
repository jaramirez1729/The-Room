/*
 * The Room - Text Based Adventure Game
 * By: Jose Adan Ramirez
 * Created on: 8/3/17
 *
 * The room is a text based adventure game that requires the user to
 * enter a series of command to guide themselves around and pass
 * the game.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "RamirezGameData.h"


// tag, description, name, location to the north east south and west,
location locations[] = {
        // Your apartment locations
        {0, "your living room. You can't leave through the front door.", "living room",
                kitchen, bathroom, NULL, NULL},

        {1, "the kitchen; there is a strange odor coming from the microwave.", "kitchen",
                NULL, NULL, livingRoom, NULL},

        {2, "the bathroom. There's a toilet and a giant hole on the wall.", "bathroom",
                NULL, NULL, NULL, livingRoom},

        // The cave location
        {3, "a dimly lit cave. There seems to be something written on a wall.", "cave entrance",
                NULL, caveEntranceEastRoom, NULL, caveEntranceWestRoom},

        {4, "a dimly lit cave.", "cave east room", NULL, caveEastDarkRoom, caveLitRoom, caveEntrance},

        {5, "a dimly lit cave. ", "cave west room", NULL, caveEntrance, NULL, NULL},

        {6, "dark room. You can't see anything, not even what you step on.", "cave dark room",
                NULL, NULL, NULL, caveEntranceEastRoom},

        {7, "a cave room where there seems to be a lot of light coming\nfrom the corner of a wall.", "cave lit room",
                    caveEntranceEastRoom, NULL, NULL, NULL},

        {8, "a forest where the sun shines through.", "forest", NULL, eastForest, NULL, westForest},

        {9, "a forest with an abandoned car on the side of the road.", "east forest", NULL, NULL, NULL, westForest},

        {10, "a forest where there is an abandoned tent.", "west forest", NULL, mainForest, NULL, NULL}
};


// Name
item items[] = {
        {"wire cutters"},
        {"padlock key"},
        {"snake coin"},
        {"car keys"}
};


// description, used description, name, location, did use, item required, item rewarded, use item description,
// can move to new location, move to location,
object objects[] = {
        {"The microwave seems to be tightly shut with wires.\nMaybe we could cut it with a tool.",
                "There is nothing unique about the microwave anymore.",
                "microwave", kitchen,  0, wireCutters, padLockKey,
                "\nYou used the wire cutters on the microwave to remove the wires. As you\nopen it, you "
                        "find a key inside of it. It looks like the smell was from\nburning metal. You hope the "
                        "key still works... but who did this?\n", 0, 0},

        {"There seems to be something clogging the toilet...\nYou reach your hand in there (gross!) only to feel "
                 "some kind of sharp tool.\nYou found a pair of wire cutters. (Whoosh!)",
                "The toilet is no longer clogged.",
                "toilet", bathroom, 0, NULL, wireCutters, "", 0, 0},

        {"The giant hole in the wall seems to be shut with a bunch of chains.\nUpon closer inspection, you notice "
                 "that there is a padlock that requires\na key.", "",
                "giant hole", bathroom, 0, padLockKey, NULL,
                "\nYou used the key on the padlock, which allowed you to remove the chains.\n\nYou are "
                        "hesitant to step in... but do you have any other choice? You\nslowly walk through the "
                        "hole only to find yourself in a cave.\n\n", 1, 3},

        {"The front door is heavily locked by a bunch of chains. It doesn't seem\nlike you can do anything about it.",
                "", "front door", livingRoom, 0, NULL, NULL, "", 0, 0},

        {"There is some kind of writing on the wall.\n\n\"The formless one leads the way.\nIf only you could see it.\"",
                "", "wall", caveEntrance, 0, NULL, NULL, "", 0, 0},

        {"You put your hands on the floor and feel something small and round.\nThe more you rub your fingers on it, the "
                 "more you feel something\nformless... almost like an engraved snake on a coin. You put it\nin your "
                 "backpack just in case.",
                "You put your hands on the floor but feel nothing but rocks.",
                "floor", caveEastDarkRoom, 0, NULL, snakeCoin, "", 0, 0},

        {"There is a small circular engraving on the wall's corner.", "", "wall's corner", caveLitRoom, 0, snakeCoin, NULL,
                "\nYou put the snake coin in the engraved circular opening... you hear\nrumbling for a few seconds "
                        "until a bright flash suddenly blinds you.\nWhen you open your eyes, you realize you are "
                        "outside in a forest now.\n\n", 1, 8},

        {"There seems to be nobody around or in the tent.\nAs you look inside, you only find a pair of car keys.\n"
                 "You take them just in case you need them.",
        "There is just an abandoned tent with nobody around it.", "tent", westForest, 0, 0, carKeys, 0, 0},

        {"There is a car on the side of the road with the door\nopen but nobody around it.",
        "", "car", eastForest, 0, carKeys, NULL, "\nYou hope that the car keys you found start the car...\n"
                                                         "As you turn them, the car turns on and you start driving home.\n\n", 0, 0}
};


// Print the description of where the user is and what is around there.
void executeLook(const char *noun) {
    if (noun != NULL && strcmp(noun, "around") == 0) {
        printf("You are in %s", locations[playerLocation].description);
        printSurroundingLocations(locations[playerLocation]);
        printf("\n");
    } else {
        printf("I don't understand what you want to see.\n");
    }
}



void printSurroundingLocations(location currentLocation) {
    if (currentLocation.northLocation)
        printf("\nThe %s is north of you.", currentLocation.northLocation->name);
    if (currentLocation.eastLocation)
        printf("\nThe %s is east of you.", currentLocation.eastLocation->name);
    if (currentLocation.southLocation)
        printf("\nThe %s is south of you.", currentLocation.southLocation->name);
    if (currentLocation.westLocation)
        printf("\nThe %s is west of you.", currentLocation.westLocation->name);
}



// Decides where to move the user based on where they are or direction.
void executeGo(const char *noun) {
    unsigned i;

    for (i = 0; i < numOfLocations; i++) {

        // Do this if the user entered a valid location name
        if (noun != NULL && strcmp(noun, locations[i].name) == 0) {

            if (i == playerLocation) {
                printf("You are already there.\n");

            } else {

                // Only move if the room is connected to the current location
                if (locations[playerLocation].northLocation
                    && strcmp(noun, locations[playerLocation].northLocation->name) == 0) {

                    playerLocation = locations[playerLocation].northLocation->tag;
                    executeLook("around");
                    return;

                } else if (locations[playerLocation].eastLocation
                           && strcmp(noun, locations[playerLocation].eastLocation->name) == 0) {

                    playerLocation = locations[playerLocation].eastLocation->tag;
                    executeLook("around");
                    return;

                } else if (locations[playerLocation].southLocation
                           && strcmp(noun, locations[playerLocation].southLocation->name) == 0) {

                    playerLocation = locations[playerLocation].southLocation->tag;
                    executeLook("around");
                    return;

                } else if (locations[playerLocation].westLocation
                           && strcmp(noun, locations[playerLocation].westLocation->name) == 0) {

                    playerLocation = locations[playerLocation].westLocation->tag;
                    executeLook("around");
                    return;
                }

                printf("There is no location around you called '%s'.\n", noun);
            }

            return;

            // Do this if the user entered a valid direction
        } else if (noun != NULL
                   && (strcmp(noun, "north") == 0 || strcmp(noun, "North") == 0
                       || strcmp(noun, "east") == 0 || strcmp(noun, "East") == 0
                       || strcmp(noun, "south") == 0 || strcmp(noun, "South") == 0
                       || strcmp(noun, "west") == 0 || strcmp(noun, "West") == 0)) {

            // Only move if the room is connected to the current location in that direction
            if (locations[playerLocation].northLocation
                && (strcmp(noun, "north") == 0 || strcmp(noun, "North") == 0)) {

                playerLocation = locations[playerLocation].northLocation->tag;
                executeLook("around");
                return;

            } else if (locations[playerLocation].eastLocation
                       && (strcmp(noun, "east") == 0 || strcmp(noun, "East") == 0)) {

                playerLocation = locations[playerLocation].eastLocation->tag;
                executeLook("around");
                return;

            } else if (locations[playerLocation].southLocation
                       && (strcmp(noun, "south") == 0 || strcmp(noun, "South") == 0)) {

                playerLocation = locations[playerLocation].southLocation->tag;
                executeLook("around");
                return;

            } else if (locations[playerLocation].westLocation
                       && (strcmp(noun, "west") == 0 || strcmp(noun, "West") == 0)) {

                playerLocation = locations[playerLocation].westLocation->tag;
                executeLook("around");
                return;

            } else {
                printf("There is nowhere to go in that direction.\n");
            }

            return;
        }
    }

    printf("I don't understand where you want to go.\n");
}


// Checks the objects that are at the locations and see if you can do anything unique
invItem *executeExamine(const char *noun, invItem *backpack) {
    unsigned int i;

    for (i = 0; i < numOfObjects; i++) {

        if (noun != NULL && strcmp(noun, objects[i].name) == 0) {

            // Check if the item to examine is in the same room
            if (objects[i].location->tag == playerLocation) {

                objects[i].didUse ? printf("%s\n", objects[i].usedDescription)
                                  : printf("%s\n", objects[i].description);


                // First check if the object requires an item
                if (objects[i].itemRequired != NULL && objects[i].didUse == 0) {

                    //Check if the user has the item required in the inventory
                    if (isItemInPossession(backpack, objects[i].itemRequired->name)) {
                        printf("%s", objects[i].useItemDescription);
                        objects[i].didUse = 1;

                        // If the object can move them, then change the user's location
                        if (objects[i].canMoveToLocation == 1) {
                            playerLocation = objects[i].moveToLocation;
                            executeLook("around");
                        } else if (strcmp(objects[i].name, "car") == 0) {
                            return NULL;
                        }

                        // Only add to the inventory if there is an item to add
                        if (objects[i].itemRewarded != NULL)
                            return inventoryItemPush(backpack, *objects[i].itemRewarded);

                        return backpack;
                    }

                    // Called if the objects doesn't need an item and just examination
                    // For example, observing the toilet at the beginning gives you
                    // wire cutters and that's it.
                } else if (objects[i].itemRequired == NULL
                           && objects[i].itemRewarded != NULL
                           && objects[i].didUse == 0) {
                    objects[i].didUse = 1;
                    return inventoryItemPush(backpack, *objects[i].itemRewarded);
                }

            } else {
                printf("There is nothing unique about examining '%s'.\n", noun);
            }

            return backpack;
        }
    }

    printf("I don't understand what you want to examine.\n");
    return backpack;
}



void executeInventory(invItem *backpack) {
    printf("\n* INVENTORY *\n");

    if (strcmp(backpack->name, "") == 0) {
        printf("You have nothing in your backpack.\n");

    } else {
        invItem *tempItem;
        for (tempItem = backpack; tempItem; tempItem = tempItem->nextItem) {
            printf("%s\n", tempItem->name);
        }
    }
}



// Adds items to the user's inventory
invItem *inventoryItemPush(invItem *backpack, item newItem) {

    // That means it's the first item, so we want to replace the name
    if (strcmp(backpack->name, "") == 0) {
        backpack->name = newItem.name;

    } else {
        invItem *tempItem = malloc(sizeof(invItem));
        tempItem->name = newItem.name;
        tempItem->nextItem = NULL;

        invItem *lastItem = backpack;
        while (lastItem->nextItem) {
            lastItem = lastItem->nextItem;
        }

        lastItem->nextItem = tempItem;
    }

    return backpack;
}



// Checks to see if the user has the right item in the inventory
int isItemInPossession(invItem *backpack, const char *name) {
    invItem *item = backpack;

    for (; item; item = item->nextItem) {
        if (strcmp(item->name, name) == 0) {
            return 1;
        }
    }

    return 0;
}
