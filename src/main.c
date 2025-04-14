#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter l'éditeur
typedef struct {
    char* buffer;
    size_t buffer_size;
    size_t buffer_capacity;
    int cursor_pos;
} Editor;

// Fonction pour initialiser l'éditeur
void init_editor(Editor* editor) {
    editor->buffer_capacity = 1024;
    editor->buffer = (char*)malloc(editor->buffer_capacity * sizeof(char));
    if (editor->buffer == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    editor->buffer[0] = '\0';
    editor->buffer_size = 0;
    editor->cursor_pos = 0;
}

// Fonction pour libérer les ressources de l'éditeur
void free_editor(Editor* editor) {
    free(editor->buffer);
}

// Fonction pour rendre le contenu du buffer
void render_editor(Editor* editor) {
    DrawText(editor->buffer, 10, 10, 20, DARKGRAY);

    // Render the cursor
    int cursor_x = 10 + MeasureText(TextSubtext(editor->buffer, 0, editor->cursor_pos), 20);
    int cursor_y = 10;
    DrawRectangleV((Vector2){cursor_x, cursor_y}, (Vector2){1, 20}, DARKGRAY);
}

// Fonction pour gérer les événements de saisie
void handle_input(Editor* editor) {
    if (IsKeyDown(KEY_BACKSPACE) && editor->cursor_pos > 0) {
        memmove(editor->buffer + editor->cursor_pos - 1, editor->buffer + editor->cursor_pos, editor->buffer_size - editor->cursor_pos + 1);
        editor->cursor_pos--;
        editor->buffer_size--;
    }

    int key = GetCharPressed();
    while (key > 0) {
        if (editor->buffer_size + 1 >= editor->buffer_capacity) {
            editor->buffer_capacity *= 2;
            editor->buffer = (char*)realloc(editor->buffer, editor->buffer_capacity * sizeof(char));
            if (editor->buffer == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        memmove(editor->buffer + editor->cursor_pos + 1, editor->buffer + editor->cursor_pos, editor->buffer_size - editor->cursor_pos + 1);
        editor->buffer[editor->cursor_pos] = (char)key;
        editor->cursor_pos++;
        editor->buffer_size++;
        key = GetCharPressed();
    }
}

int main(void) {
    // Initialisation de la fenêtre
    InitWindow(800, 600, "Text Editor");
    SetTargetFPS(60);

    Editor editor;
    init_editor(&editor);

    while (!WindowShouldClose()) {
        handle_input(&editor);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        render_editor(&editor);
        EndDrawing();
    }

    free_editor(&editor);
    CloseWindow();

    return 0;
}
