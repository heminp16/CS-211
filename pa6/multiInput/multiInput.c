#define  _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define NAME_SIZE 16

// Reverse linked list node of Boolean variable and Boolean value pairs
typedef struct var {
    char name[NAME_SIZE];
    bool val;
    struct var* prev;
} var_t;


// PROCESS A SINGLE ROW OF CIRCUIT FILE DESCRIBING A GATE TO FIND OUTPUT NAME AND VALUE
void findOutVarNameVal (
    var_t* varList,
    char* gateLine,
    char* outName,
    bool* outVal
) {

    char gate[5];
    char inName0[NAME_SIZE];
    //char inName1[NAME_SIZE];
    bool oVal = false;
    size_t inputNbr;

    if ( sscanf(gateLine, "NOT %s %s\n", inName0, outName)==2 ) {
        // It is a NOT gate
        // printf("NOT %s %s\n", inName0, out);

        bool inVal=false;

        // Traverse varList to look for existing value
        var_t* curr = varList;
        while (curr) {
            // https://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
            if ( strcmp(curr->name, inName0)==0 ) {
                inVal = curr->val;
                break;
            }
            curr = curr->prev;
        }

        // *outVal = !inVal;
        oVal = !inVal;

    } else if ( sscanf(gateLine, "%s %ld", gate, &inputNbr)==2 )  {
        // It is not a NOT gate (NAND, AND, NOR, OR, XNOR, XOR)
        var_t *curr = varList;
        var_t *inpList = calloc (inputNbr, sizeof(var_t));
        int i, idx;

        idx = strlen(gate) + ((inputNbr < 10)? 3 : 4);
        for (i = 0; i < inputNbr; i++) {
           assert (sscanf(&gateLine[idx], "%s", inpList[i].name) == 1);
           idx += strlen(inpList[i].name) + 1;
        }
        assert (sscanf(&gateLine[idx], "%s", outName) == 1);

        // Get inpList[i] current value
        while (curr) {
           for (i = 0; i < inputNbr; i++) {
              if (strcmp(curr->name, inpList[i].name) == 0) {
                 inpList[i].val = curr->val;
              }
           }
           curr = curr->prev;
        }

        // Calculate output, based on gate type, and inputs
        oVal = inpList[0].val;
        for (i = 1; i < inputNbr; i++) {
           if (strcmp(gate, "NAND") == 0) {
              oVal &= inpList[i].val;
           }
           if (strcmp(gate, "AND") == 0) {
              oVal &= inpList[i].val;
           }
           if (strcmp(gate, "NOR") == 0) {
              oVal |= inpList[i].val;
           }
           if (strcmp(gate, "OR") == 0) {
              oVal |= inpList[i].val;
           }
           if (strcmp(gate, "XNOR") == 0) {
              oVal ^= inpList[i].val;
           }
           if (strcmp(gate, "XOR") == 0) {
              oVal ^= inpList[i].val;
           }
        }
        if (strcmp(gate, "NAND") == 0 || strcmp(gate, "NOR") == 0 ||
            strcmp(gate, "XNOR") == 0) {
           oVal = !oVal;
        }
        free(inpList);
    } else {
        perror("invalid line describing gate in circuit file\n");
        exit(EXIT_FAILURE);
    }
    *outVal = oVal;
}


// PRINT A SINGLE ROW OF THE TRUTH TABLE GIVEN INITIAL ASSIGNMENTS TO CIRCUIT INPUTS
void printTruthTableRow (
    FILE* circuit_fp,
    size_t circuitInputBits // Vector of Boolean assignments for input bits
) {

    // Record input variable names
    size_t circuitInputCount;
    assert ( fscanf(circuit_fp, "INPUTVAR %ld ", &circuitInputCount)==1 );
    var_t* inputs = calloc( circuitInputCount, sizeof(var_t) ); // We use an array of var_t here
    for ( size_t i=0; i<circuitInputCount; i++ )
        assert ( fscanf(circuit_fp, "%s", inputs[i].name)==1 );
    assert ( fscanf(circuit_fp, "\n")==0 );

    // Record output variable names
    size_t circuitOutputCount;
    assert ( fscanf(circuit_fp, "OUTPUTVAR %ld ", &circuitOutputCount)==1 );
    var_t* outputs = calloc( circuitOutputCount, sizeof(var_t) ); // We use an array of var_t here
    for ( size_t i=0; i<circuitOutputCount; i++ )
        assert ( fscanf(circuit_fp, "%s", outputs[i].name)==1 );
    assert ( fscanf(circuit_fp, "\n")==0 );

    // Reversed linked list of variable structs
    var_t* varList = NULL;
    // Initialize the list with initial assignments to input variables
    for ( size_t i=0; i<circuitInputCount; i++ ) {
        var_t* temp = calloc( 1, sizeof(var_t) );
        // https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm
        strcpy(temp->name, inputs[i].name);
        temp->val = 0b1 & circuitInputBits>>i; // Each bit in input bits
        temp->prev = varList;
        varList = temp;
    }

    // Read the rest of the circuit file consisting of gates line by line
    char* line = NULL;
    size_t len = 0;
    // https://riptutorial.com/c/example/8274/get-lines-from-a-file-using-getline--

    // Read circuit file
    while (getline(&line, &len, circuit_fp)!=-1 ) {

       char outName[NAME_SIZE];
       bool outVal=false;
       findOutVarNameVal( varList, line, outName, &outVal );

       // Record this gate's outputs
       var_t* temp = calloc( 1, sizeof(var_t) );
       // https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm
       strcpy(temp->name, outName);
       temp->val = outVal;
       temp->prev = varList;
       varList = temp;
    }

    // Print the truth table
    for ( size_t i=0; i<circuitInputCount; i++ ) {
        var_t* curr = varList;
        while (curr) {
            if ( strcmp(curr->name, inputs[i].name)==0 ) {
                printf ( "%d ", curr->val );
                break;
            }
            curr = curr->prev;
        }
    }
    for ( size_t i=0; i<circuitOutputCount; i++ ) {
        var_t* curr = varList;
        while (curr) {
            if ( strcmp(curr->name, outputs[i].name)==0 ) {
                printf ( "%d ", curr->val );
                break;
            }
            curr = curr->prev;
        }
    }
    printf("\n");

    free(line);
    while (varList) {
        // printf ( "\n%s %d", varList->name, varList->val );
        var_t* temp = varList;
        varList = varList->prev;
        free(temp);
    }
    free(outputs);
    free(inputs);
}


int main(int argc, char* argv[]) {

    if (argc!=2) {
        printf("Usage: ./basicGates <circuit_file>\n");
        exit(EXIT_FAILURE);
    }

    // Open circuit file
    FILE* circuit_fp = fopen(argv[1], "r");
    if (!circuit_fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    // Peak at the input count so we know how many rows in the truth table
    size_t circuitInputCount;
    assert ( fscanf(circuit_fp, "INPUTVAR %ld ", &circuitInputCount)==1 );

    // CURRENTLY SET UP TO PRINT JUST TWO ROWS OF THE TRUTH TABLE

    // Rewind circuit file for each truth table line
    int testnbr = 1 << circuitInputCount;
    for (int i = 0; i < testnbr; i++) {
       rewind(circuit_fp);
       printTruthTableRow (circuit_fp, i);
    }

    fclose(circuit_fp);
    exit(EXIT_SUCCESS);
}
