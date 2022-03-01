package edu.colorado.csci3155.project1


sealed trait StackMachineInstruction
case object AddI extends StackMachineInstruction
case object SubI extends StackMachineInstruction
case object MultI extends StackMachineInstruction
case object DivI extends StackMachineInstruction
case object ExpI extends StackMachineInstruction
case object LogI extends StackMachineInstruction
case object SinI extends StackMachineInstruction
case object CosI extends StackMachineInstruction
case class PushI(f: Double) extends StackMachineInstruction
case object PopI extends StackMachineInstruction


object StackMachineEmulator {

    /* Function emulateSingleInstruction
        Given a list of doubles to represent a stack and a single instruction of type StackMachineInstruction
        Return a stack that results when the instruction is executed from the stack.
        Make sure you handle the error cases: eg., stack size must be appropriate for the instruction
        being executed. Division by zero, log of a non negative number
        Throw an exception or assertion violation when error happens.

     */
    def emulateSingleInstruction(stack: List[Double], ins: StackMachineInstruction): List[Double] = {
        ins match {
            case PushI(f) => {
                //println("Push-> " + f)
                stack :+ f
            }
            case PopI => {
                //println("Pop")
                stack.dropRight(1)
            }
            case AddI => {
                val nstack : List[Double] = stack.dropRight(2)
                val d1 = stack.last
                val d2 = stack.dropRight(1).last
                val ans = d1 + d2
                //println("Add-> " + d1 + "+" + d2 + "=" + ans)
                nstack :+ ans
            }
            case SubI => {
                val nstack : List[Double] = stack.dropRight(2)
                val d1 = stack.last
                val d2 = stack.dropRight(1).last
                val ans = d2 - d1
                //println("Sub-> " + d1 + "-" + d2 + "=" + ans)
                nstack :+ ans
            }
            case MultI => {
                val nstack : List[Double] = stack.dropRight(2)
                val d1 = stack.last
                val d2 = stack.dropRight(1).last
                val ans = d1 * d2
                //println("Mult-> " + d1 + "*" + d2 + "=" + ans)
                nstack :+ ans
            }
            case DivI => {
                val nstack : List[Double] = stack.dropRight(2)
                val d1 = stack.last
                val d2 = stack.dropRight(1).last
                if(d2 == 0) {
                    throw new IllegalArgumentException("Cannot divide by zero.")
                }
                val ans = d1 / d2
                //println("DivI-> " + d1 + "/" + d2 + "=" + ans )
                nstack :+ ans
            }
            case LogI => {
                val nstack : List[Double] = stack.dropRight(1)
                val d = stack.last
                if(d <= 0) {
                    throw new IllegalArgumentException("Cannot compute negative number(log n, n > 0).")
                }
                val ans = math.log(d)
                //println("Log-> " + d + "=" + ans)
                nstack :+ ans
            }
            case ExpI => {
                val nstack : List[Double] = stack.dropRight(1)
                val d = stack.last
                val ans = math.exp(d)
                //println("Exp-> " + d + "=" + ans )
                nstack :+ ans
            }
            case SinI => {
                val nstack : List[Double] = stack.dropRight(1)
                val d = stack.last
                val ans = math.sin(d)
                nstack :+ ans
            }
            case CosI => {
                val nstack : List[Double] = stack.dropRight(1)
                val d = stack.last
                val ans = math.cos(d)
                nstack :+ ans
            }
        }
    }

    /* Function emulateStackMachine
       Execute the list of instructions provided as inputs using the
       emulateSingleInstruction function.
       Use foldLeft over list of instruction rather than a for loop if you can.
       Return value must be a double that is the top of the stack after all instructions
       are executed.
     */
    def emulateStackMachine(instructionList: List[StackMachineInstruction]): Double = {
        instructionList.foldLeft(List[Double]()) {
            (acc, instruction) => {
                acc ++ emulateSingleInstruction(acc, instruction)
            }
        }.last
    }
}