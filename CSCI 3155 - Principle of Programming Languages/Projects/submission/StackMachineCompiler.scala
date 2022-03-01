package edu.colorado.csci3155.project1

object StackMachineCompiler {

    /* Function compileToStackMachineCode
        Given expression e as input, return a corresponding list of stack machine instructions.
        The type of stackmachine instructions are in the file StackMachineEmulator.scala in this same directory
        The type of Expr is in the file Expr.scala in this directory.
     */
    def compileToStackMachineCode(e: Expr): List[StackMachineInstruction] = {
        e match {
            case Const(n) => { List(PushI(n)) }
            case Plus(e1, e2) => {
                val ist_1 : List[StackMachineInstruction] = compileToStackMachineCode(e1)
                val ist_2 : List[StackMachineInstruction] = compileToStackMachineCode(e2)
                val ist: List[StackMachineInstruction] = ist_1 ++ ist_2
                return ist :+ AddI
            }
            case Minus(e1, e2) => {
                val ist_1 : List[StackMachineInstruction] = compileToStackMachineCode(e1)
                val ist_2 : List[StackMachineInstruction] = compileToStackMachineCode(e2)
                val ist = ist_1 ++ ist_2
                return ist :+ SubI
            }
            case Mult(e1, e2) => {
                val ist_1 : List[StackMachineInstruction] = compileToStackMachineCode(e1)
                val ist_2 : List[StackMachineInstruction] = compileToStackMachineCode(e2)
                val ist = ist_1 ++ ist_2
                return ist :+ MultI
            }
            case Div(e1, e2) => {
                val ist_1 : List[StackMachineInstruction] = compileToStackMachineCode(e1)
                val ist_2 : List[StackMachineInstruction] = compileToStackMachineCode(e2)
                val ist = ist_1 ++ ist_2
                return ist :+ DivI
            }
            case Exp(e) => {
                val ist : List[StackMachineInstruction] = compileToStackMachineCode(e)
                return ist :+ ExpI
            }
            case Log(e) => {
                val ist : List[StackMachineInstruction] = compileToStackMachineCode(e)
                return ist :+ LogI
            }
            case Sine(e) => {
                val ist : List[StackMachineInstruction] = compileToStackMachineCode(e)
                return ist :+ SinI
            }
            case Cosine(e) => {
                val ist : List[StackMachineInstruction] = compileToStackMachineCode(e)
                return ist :+ CosI
            }
        }
    }
}
