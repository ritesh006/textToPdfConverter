# textToPdfConverter
Here using with c programing making c application which will convert .txt to .pdf


    sample @demo for setting 
    HPDF_Page_SetFontAndSize(page, font, 12);
    HPDF_Page_SetTextLeading(page, 15); // Set line spacing

    HPDF_Page_BeginText(page);
    HPDF_Page_MoveTextPos(page, 50, y_position); // Set text position
    HPDF_Page_ShowText(page, page_title);
    HPDF_Page_EndText(page);

    /* save the document to a file 
    HPDF_SaveToFile(pdf, fname);
