/* TO BE COMPLETED HERE THE FIELDS OF THE DATA TYPE ChallengeRoomSystem */

    char *name; // name of system
    int num_of_challenges; // number of challenges in system
    Challenge *system_challenges; // challenges array
    int num_of_rooms; // number of rooms in system
    ChallengeRoom *rooms; // rooms array
    struct SVisitorsList {
        Visitor visitor;
        struct SVisitorsList *next_visitor;
    } visitor_list; // list of visitors(struct of data-visitor and ptr to next)
    int last_system_update; // last system update time
