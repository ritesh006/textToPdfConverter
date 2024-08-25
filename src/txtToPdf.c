#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"
#include <stdint.h>

// Global variable for handling errors
jmp_buf env;

// Error handling function for libharu
void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
    printf("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no, (HPDF_UINT)detail_no);
    longjmp(env, 1); // Return to the saved state in setjmp
}

// Function to convert a text file to a PDF
int demo(const char *filePath)
{
    HPDF_Doc pdf; // PDF document handle
    HPDF_Font font; // Font handle
    HPDF_Page page; // PDF page handle
    char fname[256]; // Buffer for the output PDF file name
    char line[256]; // Buffer for reading lines from the input text file
    FILE *file; // File handle for reading the input text file
    int y_position = 750; // Starting y-coordinate for text placement

    // Get the PDF file name from the user
    printf("Enter Name for Saving the file: ");
    scanf("%s", fname);

    // Append ".pdf" to the provided file name
    strcat(fname, ".pdf");

    // Create a new PDF document
    pdf = HPDF_New(error_handler, NULL);
    if (!pdf)
    {
        printf("error: cannot create PdfDoc object\n");
        return 1;
    }

    // Error handling setup
    if (setjmp(env))
    {
        HPDF_Free(pdf); // Free the PDF document on error
        return 1;
    }

    // Set compression mode for the PDF
    HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);

    // Set the font for the PDF
    font = HPDF_GetFont(pdf, "Helvetica", NULL);

    // Add a new page to the PDF document
    page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    // Open the input text file for reading
    file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Failed to open %s\n", filePath);
        HPDF_Free(pdf);
        return 1;
    }

    // Set font size and line spacing
    HPDF_Page_SetFontAndSize(page, font, 12);
    HPDF_Page_SetTextLeading(page, 15);

    // Begin adding text to the PDF page
    HPDF_Page_BeginText(page);
    HPDF_Page_MoveTextPos(page, 50, y_position); // Set the initial text position

    // Read each line from the text file and add it to the PDF
    while (fgets(line, sizeof(line), file)) {
        // Remove the newline character if present
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }

        // Show the text on the PDF page
        HPDF_Page_ShowText(page, line);

        // Move the text position down for the next line
        y_position -= 15;
        HPDF_Page_MoveTextPos(page, 0, -15); 
    }

    // End text section
    HPDF_Page_EndText(page);
    fclose(file); // Close the input text file

    // Save the PDF document to a file
    if (HPDF_SaveToFile(pdf, fname) != HPDF_OK) {
        fprintf(stderr, "Failed to save PDF file\n");
        HPDF_Free(pdf);
        return 1;
    }

    // Clean up and free the PDF document
    HPDF_Free(pdf);

    printf("PDF created successfully\n");

    return 0; // Return success
}
