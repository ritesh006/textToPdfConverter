#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <setjmp.h>
#include "hpdf.h"
#include <stdint.h>

jmp_buf env;

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no,void *user_data)
{
    printf("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no, (HPDF_UINT)detail_no);
    longjmp(env, 1);
}


int demo (const char *filePath)
{
const char *page_title = "Text Demo";

    HPDF_Doc pdf;
    HPDF_Font font;
    HPDF_Page page;
    char fname[256];
    char line[256];
    FILE *file; 
    uint8_t PAGE_PORTRAIT = 0;
    uint8_t PAGE_LANDSCAPE = 1;
    
    int y_position = 750; // Start position from top of the page
    
    
    printf("Enter Name for Saving the file: ");
    scanf("%s",fname);

    strcat(fname, ".pdf");

    pdf = HPDF_New(error_handler, NULL);
    if (!pdf)
    {
        printf("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env))
    {
        HPDF_Free(pdf);
        return 1;
    }

    /* set compression mode */
    HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);

    /* create default-font */
    font = HPDF_GetFont(pdf, "Helvetica", NULL);

    /* add a new page object. */
    page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, PAGE_PORTRAIT);

    file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Failed to open input.txt\n");
        HPDF_Free(pdf);
        return 1;
    }


    
    HPDF_Page_SetFontAndSize(page, font, 12);
    HPDF_Page_SetTextLeading(page, 15); // Set line spacing
    HPDF_Page_BeginText(page);

    while (fgets(line, sizeof(line), file)) {
        // if (y_position < 50) { // Check if we need to move to a new page
        //     HPDF_Page_EndText(page); // End text block
        //     page = HPDF_AddPage(pdf); // Add a new page
        //     HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_SIZE_A4); // Set page size
        //     HPDF_Page_BeginText(page); // Begin new text block
        //     y_position = 750; // Reset y_position for new page
        // }

        HPDF_Page_MoveTextPos(page, 50, y_position); // Set text position
        HPDF_Page_ShowText(page, line); // Add text to the PDF
        y_position -= 15; // Move down for the next line
    }

    HPDF_Page_EndText(page);
    fclose(file);

    if (HPDF_SaveToFile(pdf, fname) != HPDF_OK) {
        fprintf(stderr, "Failed to save PDF file\n");
        HPDF_Free(pdf);
        return 1;
    }



/*  sample @demo for setting 
    HPDF_Page_SetFontAndSize(page, font, 12);
    HPDF_Page_SetTextLeading(page, 15); // Set line spacing

    HPDF_Page_BeginText(page);
    HPDF_Page_MoveTextPos(page, 50, y_position); // Set text position
    HPDF_Page_ShowText(page, page_title);
    HPDF_Page_EndText(page);


    /* save the document to a file 
    HPDF_SaveToFile(pdf, fname);

*/ 






    /* clean up */
    HPDF_Free(pdf);

    printf("PDF created successfully\n");
 
}
