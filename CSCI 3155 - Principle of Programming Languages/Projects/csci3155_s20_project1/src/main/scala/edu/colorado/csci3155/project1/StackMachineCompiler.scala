package edu.colorado.csci3155.project1

object StackMachineCompiler {



    /* Function compileToStackMachineCode
        Given expression e as input, return a corresponding list of stack machine instructions.
        The type of stack machine instructions are in the file StackMachineEmulator.scala in this same directory
        The type of Expr is in the file Expr.scala in this directory.
     */
    def compileToStackMachineCode(e: Expr): List[StackMachineInstruction] =
    {
        e match
        {
            case Const(n) =>
            {
                List(PushI(n))
            }

            case Ident(id) =>
            {
                List(StoreI(id))
            }

            case Plus(e1, e2) =>
            {
                val stack1 : List[StackMachineInstruction] = compileToStackMachineCode(e1)
                val stack2 : List[StackMachineInstruction] = compileToStackMachineCode(e2)
                val full: List[StackMachineInstruction] = stack1 ++ stack2
                full :+ AddI
            }

            case Minus(e1, e2) =>
            {
                val stack1 : List[StackMachineInstruction] = compileToStackMachineCode(e1)
                val stack2 : List[StackMachineInstruction] = compileToStackMachineCode(e2)
                val full = stack1 ++ stack2
                full :+ SubI
            }

            case Mult(e1, e2) =>
            {
                val stack1 : List[StackMachineInstruction] = compileToStackMachineCode(e1)
                val stack2 : List[StackMachineInstruction] = compileToStackMachineCode(e2)
                val full = stack1 ++ stack2
                full :+ MultI
            }

            case Div(e1, e2) =>
            {
                val stack1 : List[StackMachineInstruction] = compileToStackMachineCode(e1)
                val stack2 : List[StackMachineInstruction] = compileToStackMachineCode(e2)
                val full = stack1 ++ stack2
                full :+ DivI
            }

            case Exp(e) =>
            {
                val full : List[StackMachineInstruction] = compileToStackMachineCode(e)
                full :+ ExpI
            }

            case Log(e) =>
            {
                val full : List[StackMachineInstruction] = compileToStackMachineCode(e)
                full :+ LogI
            }

            case Sine(e) =>
            {
                val full : List[StackMachineInstruction] = compileToStackMachineCode(e)
                full :+ SinI
            }

            case Cosine(e) =>
            {
                val full : List[StackMachineInstruction] = compileToStackMachineCode(e)
                full :+ CosI
            }

            case Let(id, e1, e2) =>
            {
                val stack1 : List[StackMachineInstruction] = compileToStackMachineCode(e1)
                val stack2 : List[StackMachineInstruction] = compileToStackMachineCode(e2)
                stack1 ++ List(LoadI(id)) ++ stack2

            }

        }
    }
}
