

// #include "header.h"
// #include <hpdf.h>

// int txtToPdfConverterFunc()
// {
//     HPDF_Doc pdf;
//     HPDF_Page page;
//     const char *filename = "output.pdf";
//     HPDF_REAL height, width;

//     // Create PDF document
//     pdf = HPDF_New(NULL, NULL);
//     if (!pdf) {
//         printf("Error: Unable to create PDF document.\n");
//         return EXIT_FAILURE;
//     }

//     // Add a new page to the document
//     page = HPDF_AddPage(pdf);
//     if (!page) {
//         printf("Error: Unable to add page to the PDF document.\n");
//         HPDF_Free(pdf);
//         return EXIT_FAILURE;
//     }

//     // Set page size (A4 by default)
//     HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

//     // Get page dimensions
//     width = HPDF_Page_GetWidth(page);
//     height = HPDF_Page_GetHeight(page);

//     // Set font and font size
//     HPDF_Page_SetFontAndSize(page, HPDF_LoadStandardFont(pdf, "Helvetica"), 12.0);

//     // Write text to the page
//     HPDF_Page_BeginText(page);
//     HPDF_Page_MoveTextPos(page, 50, height - 50);
//     HPDF_Page_ShowText(page, "Hello, World!");
//     HPDF_Page_EndText(page);

//     // Save the document to a file
//     if (HPDF_SaveToFile(pdf, filename) != HPDF_OK) {
//         printf("Error: Unable to save PDF document to file.\n");
//         HPDF_Free(pdf);
//         return EXIT_FAILURE;
//     }

//     // Clean up
//     HPDF_Free(pdf);

//     printf("PDF document created successfully: %s\n", filename);

//    return EXIT_SUCCESS;

//     }