add_library(email_client_lib
    core/engine.c
    protocols/imap.c
    protocols/smtp.c
    protocols/pop3.c
    ui/main_window.c
    ui/compose_window.c
    database/db_manager.c
    utils/config.c
    utils/logger.c
)

target_link_libraries(email_client_lib
    ${GTK3_LIBRARIES}
    ${CURL_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    ${SQLite3_LIBRARIES}
)
