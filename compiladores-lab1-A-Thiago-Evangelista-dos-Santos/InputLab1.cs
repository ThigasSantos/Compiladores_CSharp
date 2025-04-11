  class empOps
  {
    
     public static void TableUDF( Double factor, out String name,
                       out String position, out Double salary,
                       Int16 factorNullInd, out Int16 nameNullInd,
                       out Int16 positionNullInd, out Int16 salaryNullInd,
                       ref String sqlState, String funcName,
                       String specName, ref String sqlMessageText,
                       Byte[] scratchPad, Int32 callType)
     {

        Int16 intRow = 0;

        // Create an array of Person type information
        Person[] Staff = new
        Person[3];
        Staff[0] = new Person("Gwen", "Developer", 10000);
        Staff[1] = new Person("Andrew", "Developer", 20000);
        Staff[2] = new Person("Liu", "Team Leader", 30000); 

        salary = 0;
        name = position = "";       
        nameNullInd = positionNullInd = salaryNullInd = -1;

        switch(callType)
        {
           case (-2):  // Case SQLUDF_TF_FIRST:
             break;

           case (-1):  // Case SQLUDF_TF_OPEN:
             intRow = 1;
             scratchPad[0] = (Byte)intRow;  // Write to scratchpad
             break;
           case (0):   // Case SQLUDF_TF_FETCH:
             intRow = (Int16)scratchPad[0];
             if (intRow > Staff.Length)
             {
                sqlState = "02000";  // Return an error SQLSTATE
             }
             else
             {
                // Generate a row in the output table 
                // based on the Staff array data.
                name =
                Staff[intRow-1].getName();
                position = Staff[intRow-1].getPosition();
                salary = (Staff[intRow-1].getSalary()) * factor;
                nameNullInd = 0;
                positionNullInd = 0;
                salaryNullInd = 0;
             }
             intRow++;
             scratchPad[0] = (Byte)intRow;  // Write scratchpad
             break;

           case (1):   // Case SQLUDF_TF_CLOSE:
             break;
     
           case (2):   // Case SQLUDF_TF_FINAL:
             break;
        }
     }
  } 