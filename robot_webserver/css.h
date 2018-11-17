const char css[] PROGMEM =\
"    .onoffswitch { \
        position: relative; width: 180px; \
        -webkit-user-select:none; -moz-user-select:none; -ms-user-select: none; \
    } \
    .onoffswitch-checkbox { \
        display: none; \
    } \
    .onoffswitch-label { \
        display: block; overflow: hidden; cursor: pointer; \
        border: 2px solid ; border-radius: 11px; \
    } \
    .onoffswitch-inner { \
        display: block; width: 200%; margin-left: -100%; \
        transition: margin 0.3s ease-in 0s; \
    } \
    .onoffswitch-inner:before, .onoffswitch-inner:after { \
        display: block; float: left; width: 50%; height: 67px; padding: 0; line-height: 67px; \
        font-size: 40px; color: white; font-family: Trebuchet, Arial, sans-serif; font-weight: bold; \
        box-sizing: border-box; \
    } \
    .onoffswitch-inner:before { \
        content: \"ON\"; \
        padding-left: 21px; \
        background-color: #34A7C1; color: #FFFFFF; \
    } \
    .onoffswitch-inner:after { \
        content: \"OFF\"; \
        padding-right: 21px; \
        background-color: #EEEEEE; color: #999999; \
        text-align: right; \
    } \
    .onoffswitch-switch { \
        display: block; width: 48px; margin: 9.5px; \
        background: #FFFFFF; \
        position: absolute; top: 0; bottom: 0; \
        right: 109px; \
        border: 2px solid ; border-radius: 11px; \
        transition: all 0.3s ease-in 0s;  \
    } \
    .onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-inner { \
        margin-left: 0; \
    } \
    .onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-switch { \
        right: 0px;  \
    }";
