# Style Guideline

## Classes

-   The class name should be written in PascalCase

    ```cpp
    class LinkedList
    ```

## Functions & Variables

-   Function and variable names should be written in camelCase
-   Consider using `const` whenever applicable, especially for member functions that don't modify the object

    ```cpp
    void isEmpty() const;
    int newData;
    ```

## Constants

-   Use all uppercase with underscores to separate words (e.g., `MAX_SIZE`)

## Pointers & References

-   Clearly separate type name from variable name, pointer (\*), and reference (&) type designators are to be placed next to the type name without any whitespace. Variable names should then be placed after a whitespace.

    **Do:**

    ```cpp
    int* ptr;
    int& value;
    ```

    **Don't:**

    ```cpp
    int *ptr;
    int &value;
    ```

## Pointers

-   Pointers' names should end with `Ptr` to make it clear

    ```cpp
    Node* headPtr;
    Node* frontPtr;
    ```

## File Names

-   Match the filename with the class name. For non-class files, use PascalCase and choose a name that states the primary purpose of the file

## Formatting

-   **Indentation**: Use tabs for indentation, with a width equivalent to four spaces
-   **Brace Placement**: Opening braces should be placed on a new line

    **Do:**

    ```cpp
    function
    {
    	//function body
    }
    ```

    **Don't:**

    ```cpp
    function{
    //function body
    }
    ```

## Branch Naming

-   **Feature Branches:** `feature/<short-description>`

    -   Example: `feature/unit-generator-class`

-   **Bug Fix Branches:** `bugfix/<issue-number>-<short-description>`
    -   Example: `bugfix/123-fix-crash-on-army-joining`

## Best Practices

-   Use of `nullptr` is preferred over `NULL` to adhere to modern C++ practices // To be confirmed
-   Avoid `using namespace std`
-   Avoid using Hungarian notation:
    As **the C++ Core Guidelines strongly discourage the use of the Hungarian method**. The guidelines advocate for using clear and descriptive names that reflect the purpose of variables and functions without relying on prefixes to convey their types as in semantic naming.

    Examples:

    ```cpp
    Hungarian notation       // Old variable name
    string txtTextBox        // TextBox
    string frmInputForm      // InputForm
    ```

    [For more info](https://www.lenovo.com/us/en/glossary/what-is-hungarian-notation/?orgRef=https%253A%252F%252Fwww.google.com%252F)
