#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_NAME_LEN 51
#define MAX_NAME_LENGTH 50 
#define MIN_PRODUCTS 1
#define MAX_PRODUCTS 100
#define MIN_PRODUCT_ID 1
#define MAX_PRODUCT_ID 10000
#define MIN_PRICE 0.0f
#define MAX_PRICE 100000.0f
#define MIN_QUANTITY 0
#define MAX_QUANTITY 1000000

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float price;
    int quantity;
} Product;

void displayMenu();
void clearInputBuffer();
bool containsSpecialChars(const char *name);
void readProductName(char *name_buffer);
void inputProducts(Product **products, int *count);
void runMenuLoop(Product **products, int *count);
void addProduct(Product **products, int *count);
void viewProducts(Product *products, int count);
void updateQuantity(Product *products, int count);
void searchByID(Product *products, int count);
void searchByName(Product *products, int count);
void searchByPriceRange(Product *products, int count);
void deleteProduct(Product **products, int *count);
int findProductByID(Product *products, int count, int id);

int main() {
    int initialCount;
    Product *products = NULL;

    while (true) {
        printf("Enter initial number of products: ");
        if (scanf("%d", &initialCount) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (initialCount >= MIN_PRODUCTS && initialCount <= MAX_PRODUCTS) {
            break;
        }
        printf("Initial product count must be between %d and %d.\n", MIN_PRODUCTS, MAX_PRODUCTS);
    }

    products = (Product *)calloc(initialCount, sizeof(Product));
    if (products == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    inputProducts(&products, &initialCount);
    
    runMenuLoop(&products, &initialCount);

    return 0;
}

void runMenuLoop(Product **products, int *count) {
    int choice;
    
    while (true) {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            choice = 0;
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addProduct(products, count);
                break;
            case 2:
                viewProducts(*products, *count);
                break;
            case 3:
                updateQuantity(*products, *count);
                break;
            case 4:
                searchByID(*products, *count);
                break;
            case 5:
                searchByName(*products, *count);
                break;
            case 6:
                searchByPriceRange(*products, *count);
                break;
            case 7:
                deleteProduct(products, count);
                break;
            case 8:
                free(*products);
                *products = NULL;
                printf("Memory released successfully. Exiting program...\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void displayMenu() {
    printf("\n========= INVENTORY MENU =========\n");
    printf("1. Add New Product\n");
    printf("2. View All Products\n");
    printf("3. Update Quantity\n");
    printf("4. Search Product by ID\n");
    printf("5. Search Product by Name\n");
    printf("6. Search Product by Price Range\n");
    printf("7. Delete Product\n");
    printf("8. Exit\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool containsSpecialChars(const char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalnum(name[i]) && name[i] != ' ' && name[i] != '-' && name[i] != '\'') {
            return true;
        }
    }
    return false;
}

void readProductName(char *name_buffer) {
    while (true) {
        printf("Product Name: ");
        if (fgets(name_buffer, MAX_NAME_LEN, stdin)) {
            name_buffer[strcspn(name_buffer, "\n")] = 0;
            
            if (strlen(name_buffer) == 0) {
                printf("Product name cannot be empty.\n");
            } else if (strlen(name_buffer) > MAX_NAME_LENGTH) {
                printf("Product name is too long (Max %d chars).\n", MAX_NAME_LENGTH);
            } else if (containsSpecialChars(name_buffer)) {
                printf("Product name contains invalid special characters (Only letters, numbers, space, hyphen, and apostrophe allowed).\n");
            } else {
                return;
            }
        } else {
            printf("Error reading input.\n");
            clearInputBuffer();
        }
    }
}

void inputProducts(Product **products, int *count) {
    for (int i = 0; i < *count; i++) {
        printf("\nEnter details for product %d:\n", i + 1);
        
        while (true) {
            printf("Product ID: ");
            if (scanf("%d", &(*products)[i].id) != 1) {
                printf("Invalid ID input.\n");
                clearInputBuffer();
                continue;
            }
            clearInputBuffer();

            if ((*products)[i].id >= MIN_PRODUCT_ID && (*products)[i].id <= MAX_PRODUCT_ID) {
                break;
            }
            printf("Product ID must be between %d and %d.\n", MIN_PRODUCT_ID, MAX_PRODUCT_ID);
        }

        readProductName((*products)[i].name);

        while (true) {
            printf("Product Price: ");
            if (scanf("%f", &(*products)[i].price) != 1) {
                printf("Invalid Price input.\n");
                clearInputBuffer();
                continue;
            }
            clearInputBuffer();
            
            if ((*products)[i].price >= MIN_PRICE && (*products)[i].price <= MAX_PRICE) {
                break;
            }
            printf("Product Price must be between %.2f and %.2f.\n", MIN_PRICE, MAX_PRICE);
        }

        while (true) {
            printf("Product Quantity: ");
            if (scanf("%d", &(*products)[i].quantity) != 1) {
                printf("Invalid Quantity input.\n");
                clearInputBuffer();
                continue;
            }
            clearInputBuffer();
            
            if ((*products)[i].quantity >= MIN_QUANTITY && (*products)[i].quantity <= MAX_QUANTITY) {
                break;
            }
            printf("Product Quantity must be between %d and %d.\n", MIN_QUANTITY, MAX_QUANTITY);
        }
    }
}

void addProduct(Product **products, int *count) {
    Product *temp = (Product *)realloc(*products, (*count + 1) * sizeof(Product));
    
    if (temp == NULL) {
        printf("Memory reallocation failed!\n");
        return;
    }
    *products = temp;

    printf("\nEnter new product details:\n");

    while (true) {
        printf("Product ID: ");
        if (scanf("%d", &(*products)[*count].id) != 1) {
            printf("Invalid ID input.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        if ((*products)[*count].id < MIN_PRODUCT_ID || (*products)[*count].id > MAX_PRODUCT_ID) {
            printf("Product ID must be between %d and %d.\n", MIN_PRODUCT_ID, MAX_PRODUCT_ID);
            continue;
        }

        int duplicate_index = findProductByID(*products, *count, (*products)[*count].id);
        if (duplicate_index != -1) {
            printf("Error: Product ID %d already exists. Please use a unique ID.\n", (*products)[*count].id);
            continue;
        }
        break;
    }

    readProductName((*products)[*count].name);

    while (true) {
        printf("Product Price: ");
        if (scanf("%f", &(*products)[*count].price) != 1) {
            printf("Invalid Price input.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        if ((*products)[*count].price >= MIN_PRICE && (*products)[*count].price <= MAX_PRICE) {
            break;
        }
        printf("Product Price must be between %.2f and %.2f.\n", MIN_PRICE, MAX_PRICE);
    }

    while (true) {
        printf("Product Quantity: ");
        if (scanf("%d", &(*products)[*count].quantity) != 1) {
            printf("Invalid Quantity input.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        if ((*products)[*count].quantity >= MIN_QUANTITY && (*products)[*count].quantity <= MAX_QUANTITY) {
            break;
        }
        printf("Product Quantity must be between %d and %d.\n", MIN_QUANTITY, MAX_QUANTITY);
    }

    (*count)++;
    printf("Product added successfully!\n");
}

void viewProducts(Product *products, int count) {
    if (count == 0) {
        printf("\n========= PRODUCT LIST IS EMPTY =========\n");
        return;
    }
    printf("\n========= PRODUCT LIST =========\n");
    for (int i = 0; i < count; i++) {
        printf("Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n",
               products[i].id, products[i].name, products[i].price, products[i].quantity);
    }
}

void updateQuantity(Product *products, int count) {
    int id, newQty, index;
    printf("Enter Product ID to update quantity: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    index = findProductByID(products, count, id);
    if (index == -1) {
        printf("Product not found!\n");
        return;
    }

    while (true) {
        printf("Enter new Quantity: ");
        if (scanf("%d", &newQty) != 1) {
            printf("Invalid quantity input.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (newQty >= MIN_QUANTITY && newQty <= MAX_QUANTITY) {
            products[index].quantity = newQty;
            printf("Quantity updated successfully!\n");
            return;
        }
        printf("New Quantity must be between %d and %d.\n", MIN_QUANTITY, MAX_QUANTITY);
    }
}

void searchByID(Product *products, int count) {
    int id, index;
    printf("Enter Product ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    index = findProductByID(products, count, id);
    if (index == -1) {
        printf("Product not found!\n");
        return;
    }

    printf("Product Found: Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n",
               products[index].id, products[index].name, products[index].price, products[index].quantity);
}

void searchByName(Product *products, int count) {
    char searchName[MAX_NAME_LEN];
    bool found = false;

    printf("Enter name to search (partial allowed): ");
    readProductName(searchName);

    printf("Products Found:\n");
    for (int i = 0; i < count; i++) {
        if (strstr(products[i].name, searchName) != NULL) {
            printf("Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n",
                   products[i].id, products[i].name, products[i].price, products[i].quantity);
            found = true;
        }
    }

    if (!found) {
        printf("No products found with that name.\n");
    }
}

void searchByPriceRange(Product *products, int count) {
    float minPrice, maxPrice;
    bool found = false;

    printf("Enter minimum price: ");
    if (scanf("%f", &minPrice) != 1) {
        printf("Invalid price input.\n");
        clearInputBuffer();
        return;
    }
    printf("Enter maximum price: ");
    if (scanf("%f", &maxPrice) != 1) {
        printf("Invalid price input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (minPrice > maxPrice || minPrice < MIN_PRICE || maxPrice > MAX_PRICE) {
        printf("Invalid price range or bounds exceeded.\n");
        return;
    }

    printf("Products in price range:\n");
    for (int i = 0; i < count; i++) {
        if (products[i].price >= minPrice && products[i].price <= maxPrice) {
            printf("Product ID: %d | Name: %s | Price: %.2f | Quantity: %d\n",
                   products[i].id, products[i].name, products[i].price, products[i].quantity);
            found = true;
        }
    }

    if (!found) {
        printf("No products found in that price range.\n");
    }
}

void deleteProduct(Product **products, int *count) {
    int id, index;
    printf("Enter Product ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    index = findProductByID(*products, *count, id);
    if (index == -1) {
        printf("Product not found!\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        (*products)[i] = (*products)[i + 1];
    }

    (*count)--;
    
    Product *temp = (Product *)realloc(*products, (*count) * sizeof(Product));

    if (*count > 0 && temp == NULL) {
         printf("Warning: Memory could not be shrunk, but product was successfully deleted.\n");
    } else {
        *products = temp;
    }
    
    printf("Product deleted successfully!\n");
}
