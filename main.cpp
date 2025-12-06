#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TASKS 100
#define TITLE_LENGTH 50
#define DESC_LENGTH 200
#define FILENAME "tasks.txt"

typedef struct {
    int id;
    char title[TITLE_LENGTH];
    char description[DESC_LENGTH];
    int priority;
    int completed; // 0 — нет, 1 — да
} Task;

Task tasks[MAX_TASKS];
int task_count = 0;
int next_id = 1;

// Функция для очистки буфера ввода
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Функция для безопасного ввода строки
void safe_input_string(char *buffer, int max_length) {
    if (fgets(buffer, max_length, stdin) != NULL) {
        // Удаляем символ новой строки
        buffer[strcspn(buffer, "\n")] = 0;
    } else {
        buffer[0] = 0; // Если ввод не удался, устанавливаем пустую строку
    }
}

// Функция для поиска задачи по ID
int find_task_index_by_id(int id) {
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Функция проверки на дубликаты по названию
int is_duplicate_title(const char *title) {
    for (int i = 0; i < task_count; i++) {
        if (strcasecmp(tasks[i].title, title) == 0) {
            return 1;
        }
    }
    return 0;
}

// 1. Добавление задачи
void add_task() {
    if (task_count >= MAX_TASKS) {
        printf("Достигнуто максимальное количество задач!\n");
        return;
    }
    
    Task new_task;
    new_task.id = next_id++;
    new_task.completed = 0;
    
    printf("\n=== Добавление новой задачи ===\n");
    
    // Ввод названия с проверкой на дубликаты
    do {
        printf("Введите название задачи (макс. %d символов): ", TITLE_LENGTH - 1);
        safe_input_string(new_task.title, TITLE_LENGTH);
        
        if (strlen(new_task.title) == 0) {
            printf("Название не может быть пустым!\n");
            continue;
        }
        
        if (is_duplicate_title(new_task.title)) {
            printf("Задача с таким названием уже существует! Введите другое название.\n");
        } else {
            break;
        }
    } while (1);
    
    // Ввод описания
    printf("Введите описание задачи (макс. %d символов): ", DESC_LENGTH - 1);
    safe_input_string(new_task.description, DESC_LENGTH);
    
    // Ввод приоритета с проверкой
    do {
        printf("Введите приоритет (1-10, где 10 - наивысший): ");
        scanf("%d", &new_task.priority);
        clear_input_buffer();
        
        if (new_task.priority < 1 || new_task.priority > 10) {
            printf("Приоритет должен быть от 1 до 10!\n");
        } else {
            break;
        }
    } while (1);
    
    // Добавление задачи в массив
    tasks[task_count++] = new_task;
    printf("Задача успешно добавлена! ID задачи: %d\n", new_task.id);
}

// 2. Удаление задачи
void remove_task() {
    if (task_count == 0) {
        printf("Список задач пуст!\n");
        return;
    }
    
    printf("\n=== Удаление задачи ===\n");
    print_tasks();
    
    int id;
    printf("Введите ID задачи для удаления: ");
    scanf("%d", &id);
    clear_input_buffer();
    
    int index = find_task_index_by_id(id);
    if (index == -1) {
        printf("Задача с ID %d не найдена!\n", id);
        return;
    }
    
    // Подтверждение удаления
    printf("Вы действительно хотите удалить задачу \"%s\"? (y/n): ", tasks[index].title);
    char confirm;
    scanf("%c", &confirm);
    clear_input_buffer();
    
    if (confirm == 'y' || confirm == 'Y') {
        // Сдвигаем все задачи после удаляемой
        for (int i = index; i < task_count - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        task_count--;
        printf("Задача успешно удалена!\n");
    } else {
        printf("Удаление отменено.\n");
    }
}

// 3. Редактирование задачи
void edit_task() {
    if (task_count == 0) {
        printf("Список задач пуст!\n");
        return;
    }
    
    printf("\n=== Редактирование задачи ===\n");
    print_tasks();
    
    int id;
    printf("Введите ID задачи для редактирования: ");
    scanf("%d", &id);
    clear_input_buffer();
    
    int index = find_task_index_by_id(id);
    if (index == -1) {
        printf("Задача с ID %d не найдена!\n", id);
        return;
    }
    
    printf("\nРедактирование задачи: %s\n", tasks[index].title);
    printf("1. Изменить название\n");
    printf("2. Изменить описание\n");
    printf("3. Изменить приоритет\n");
    printf("4. Изменить статус выполнения\n");
    printf("0. Отмена\n");
    
    int choice;
    printf("Выберите опцию: ");
    scanf("%d", &choice);
    clear_input_buffer();
    
    switch (choice) {
        case 1: {
            char new_title[TITLE_LENGTH];
            do {
                printf("Введите новое название: ");
                safe_input_string(new_title, TITLE_LENGTH);
                
                if (strlen(new_title) == 0) {
                    printf("Название не может быть пустым!\n");
                    continue;
                }
                
                if (strcasecmp(tasks[index].title, new_title) != 0 && is_duplicate_title(new_title)) {
                    printf("Задача с таким названием уже существует! Введите другое название.\n");
                } else {
                    strcpy(tasks[index].title, new_title);
                    printf("Название обновлено!\n");
                    break;
                }
            } while (1);
            break;
        }
        case 2:
            printf("Введите новое описание: ");
            safe_input_string(tasks[index].description, DESC_LENGTH);
            printf("Описание обновлено!\n");
            break;
        case 3:
            do {
                printf("Введите новый приоритет (1-10): ");
                scanf("%d", &tasks[index].priority);
                clear_input_buffer();
                
                if (tasks[index].priority < 1 || tasks[index].priority > 10) {
                    printf("Приоритет должен быть от 1 до 10!\n");
                } else {
                    printf("Приоритет обновлен!\n");
                    break;
                }
            } while (1);
            break;
        case 4:
            printf("Текущий статус: %s\n", tasks[index].completed ? "Выполнена" : "Не выполнена");
            printf("Установить как (0 - не выполнена, 1 - выполнена): ");
            scanf("%d", &tasks[index].completed);
            clear_input_buffer();
            printf("Статус обновлен!\n");
            break;
        case 0:
            printf("Редактирование отменено.\n");
            break;
        default:
            printf("Неверный выбор!\n");
    }
}

// 4. Пометка задачи как выполненной
void mark_task_completed() {
    if (task_count == 0) {
        printf("Список задач пуст!\n");
        return;
    }
    
    printf("\n=== Пометка задачи как выполненной ===\n");
    print_tasks();
    
    int id;
    printf("Введите ID задачи для пометки как выполненной: ");
    scanf("%d", &id);
    clear_input_buffer();
    
    int index = find_task_index_by_id(id);
    if (index == -1) {
        printf("Задача с ID %d не найдена!\n", id);
        return;
    }
    
    if (tasks[index].completed) {
        printf("Задача уже отмечена как выполненная!\n");
    } else {
        tasks[index].completed = 1;
        printf("Задача \"%s\" отмечена как выполненная!\n", tasks[index].title);
    }
}

// Функция сравнения для сортировки по приоритету (по убыванию)
int compare_by_priority(const void *a, const void *b) {
    Task *task1 = (Task *)a;
    Task *task2 = (Task *)b;
    return task2->priority - task1->priority;
}

// Функция сравнения для сортировки по статусу (выполненные последними)
int compare_by_status(const void *a, const void *b) {
    Task *task1 = (Task *)a;
    Task *task2 = (Task *)b;
    return task1->completed - task2->completed;
}

// 5. Просмотр всех задач
void print_tasks() {
    if (task_count == 0) {
        printf("Список задач пуст!\n");
        return;
    }
    
    printf("\n=== Список всех задач ===\n");
    
    int sort_choice;
    printf("Сортировать по:\n");
    printf("1. По умолчанию (по ID)\n");
    printf("2. По приоритету\n");
    printf("3. По статусу выполнения\n");
    printf("Выберите опцию сортировки: ");
    scanf("%d", &sort_choice);
    clear_input_buffer();
    
    // Создаем временный массив для сортировки
    Task temp_tasks[MAX_TASKS];
    memcpy(temp_tasks, tasks, sizeof(Task) * task_count);
    
    // Сортируем в зависимости от выбора
    switch (sort_choice) {
        case 2:
            qsort(temp_tasks, task_count, sizeof(Task), compare_by_priority);
            break;
        case 3:
            qsort(temp_tasks, task_count, sizeof(Task), compare_by_status);
            break;
        default:
            // Не сортируем - оставляем по ID
            break;
    }
    
    printf("\n┌─────┬────────────────────────────────────┬────────────────────────────────────┬──────────┬────────────┐\n");
    printf("│ ID  │ Название                           │ Описание                           │ Приоритет│ Статус     │\n");
    printf("├─────┼────────────────────────────────────┼────────────────────────────────────┼──────────┼────────────┤\n");
    
    for (int i = 0; i < task_count; i++) {
        printf("│ %3d │ %-34s │ %-34s │ %8d │ %-10s │\n",
               temp_tasks[i].id,
               temp_tasks[i].title,
               temp_tasks[i].description,
               temp_tasks[i].priority,
               temp_tasks[i].completed ? "Выполнена" : "Не выполнена");
    }
    
    printf("└─────┴────────────────────────────────────┴────────────────────────────────────┴──────────┴────────────┘\n");
    printf("Всего задач: %d\n", task_count);
}

// 6. Сохранение задач в файл
void save_tasks_to_file() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла для записи!\n");
        return;
    }
    
    // Сохраняем next_id для корректного продолжения нумерации
    fprintf(file, "%d\n", next_id);
    
    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%d|%s|%s|%d|%d\n",
                tasks[i].id,
                tasks[i].title,
                tasks[i].description,
                tasks[i].priority,
                tasks[i].completed);
    }
    
    fclose(file);
    printf("Задачи успешно сохранены в файл %s!\n", FILENAME);
}

// 7. Загрузка задач из файла
void load_tasks_from_file() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Файл с задачами не найден. Будет создан новый.\n");
        return;
    }
    
    // Считываем next_id
    fscanf(file, "%d\n", &next_id);
    
    task_count = 0;
    while (!feof(file) && task_count < MAX_TASKS) {
        char line[500];
        if (fgets(line, sizeof(line), file) == NULL) break;
        
        // Удаляем символ новой строки
        line[strcspn(line, "\n")] = 0;
        
        if (strlen(line) == 0) continue;
        
        // Разбираем строку
        char *token;
        Task task;
        
        token = strtok(line, "|");
        if (token) task.id = atoi(token);
        
        token = strtok(NULL, "|");
        if (token) strncpy(task.title, token, TITLE_LENGTH - 1);
        
        token = strtok(NULL, "|");
        if (token) strncpy(task.description, token, DESC_LENGTH - 1);
        
        token = strtok(NULL, "|");
        if (token) task.priority = atoi(token);
        
        token = strtok(NULL, "|");
        if (token) task.completed = atoi(token);
        
        tasks[task_count++] = task;
    }
    
    fclose(file);
    printf("Загружено %d задач из файла %s\n", task_count, FILENAME);
}

// Главное меню
void display_menu() {
    printf("\n=== Менеджер задач ===\n");
    printf("1. Добавить задачу\n");
    printf("2. Удалить задачу\n");
    printf("3. Редактировать задачу\n");
    printf("4. Пометить задачу как выполненную\n");
    printf("5. Просмотр всех задач\n");
    printf("6. Сохранить задачи\n");
    printf("7. Загрузить задачи\n");
    printf("0. Выход\n");
    printf("Выберите опцию: ");
}

// Главная функция
int main() {
    int choice;
    
    // Загружаем задачи при запуске
    load_tasks_from_file();
    
    do {
        display_menu();
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                add_task();
                break;
            case 2:
                remove_task();
                break;
            case 3:
                edit_task();
                break;
            case 4:
                mark_task_completed();
                break;
            case 5:
                print_tasks();
                break;
            case 6:
                save_tasks_to_file();
                break;
            case 7:
                load_tasks_from_file();
                break;
            case 0:
                printf("Выход из программы...\n");
                // Автоматически сохраняем при выходе
                save_tasks_to_file();
                break;
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
    } while (choice != 0);
    
    return 0;
}