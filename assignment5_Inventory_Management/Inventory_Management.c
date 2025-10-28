#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LEN 51

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float price;
    int quantity;
} Product;

void displayMenu();
void clearInputBuffer();
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

    printf("Enter initial number of products: ");
    if (scanf("%d", &initialCount) != 1) {
        printf("Invalid input. Exiting.\n");
        return 1;
    }
    clearInputBuffer();

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

void readProductName(char *name_buffer) {
    if (fgets(name_buffer, MAX_NAME_LEN, stdin)) {
        name_buffer[strcspn(name_buffer, "\n")] = 0;
    }
}

int findProductByID(Product *products, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (products[i].id == id) {
            return i;
        }
    }
    return -1;
}

void inputProducts(Product **products, int *count) {
    for (int i = 0; i < *count; i++) {
        printf("\nEnter details for product %d:\n", i + 1);
        printf("Product ID: ");
        scanf("%d", &(*products)[i].id);
        clearInputBuffer();
        
        printf("Product Name: ");
        readProductName((*products)[i].name);

        printf("Product Price: ");
        scanf("%f", &(*products)[i].price);

        printf("Product Quantity: ");
        scanf("%d", &(*products)[i].quantity);
        clearInputBuffer();
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
    printf("Product ID: ");
    scanf("%d", &(*products)[*count].id);
    clearInputBuffer();
    
    printf("Product Name: ");
    readProductName((*products)[*count].name);

    printf("Product Price: ");
    scanf("%f", &(*products)[*count].price);
    
    printf("Product Quantity: ");
    scanf("%d", &(*products)[*count].quantity);
    clearInputBuffer();

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
    scanf("%d", &id);
    clearInputBuffer();

    index = findProductByID(products, count, id);
    if (index == -1) {
        printf("Product not found!\n");
        return;
    }

    printf("Enter new Quantity: ");
    if (scanf("%d", &newQty) != 1 || newQty < 0) {
        printf("Invalid quantity input. Update failed.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    products[index].quantity = newQty;
    printf("Quantity updated successfully!\n");
}

void searchByID(Product *products, int count) {
    int id, index;
    printf("Enter Product ID to search: ");
    scanf("%d", &id);
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
    scanf("%f", &minPrice);
    printf("Enter maximum price: ");
    scanf("%f", &maxPrice);
    clearInputBuffer();

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
    scanf("%d", &id);
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