char*
drop_print(drop _drop){
        GString *string;

        string = g_string_new("");
        g_string_printf(string,
                        "Drop, Value: %c\nLength: %d, Velocity: %d\nX: %d, Y: %d\n",
                        _drop.value, _drop.length, _drop.velocity,
                        _drop.position_x, _drop.position_y);

        printf("%s\n", string->str);

        return string->str;
}

