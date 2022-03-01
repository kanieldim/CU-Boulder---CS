package edu.colorado.csci3155.project1


/* -- Here are all the instructions to be supported --*/
sealed trait StackMachineInstruction
case class LoadI(s: String) extends StackMachineInstruction
case class  StoreI(s: String) extends StackMachineInstruction
case class PushI(f: Double) extends StackMachineInstruction
case object AddI extends StackMachineInstruction
case object SubI extends StackMachineInstruction
case object MultI extends StackMachineInstruction
case object DivI extends StackMachineInstruction
case object ExpI extends StackMachineInstruction
case object LogI extends StackMachineInstruction
case object SinI extends StackMachineInstruction
case object CosI extends StackMachineInstruction
case object PopI extends StackMachineInstruction


object StackMachineEmulator
{



    /* Function emulateSingleInstruction
        Given a list of doubles to represent a stack
              a map from string to double precision numbers for the environment
        and   a single instruction of type StackMachineInstruction
        Return a tuple that contains the
              modified stack that results when the instruction is executed.
              modified environment that results when the instruction is executed.

        Make sure you handle the error cases: eg., stack size must be appropriate for the instruction
        being executed. Division by zero, log of a non negative number
        Throw an exception or assertion violation when error happens.
     */
    def emulateSingleInstruction(stack: List[Double],
                                 env: Map[String, Double],
                                 ins: StackMachineInstruction): (List[Double], Map[String, Double]) =
    {
        ins match
        {

            case LoadI(s) =>
            {
                if (stack.length > 0 )
                {
                    val stack_head = stack.head
                    val stack_slice = stack.slice(1, stack.length)
                    (stack_slice, env + (s -> stack_head))
                }
                else
                {
                    throw new IllegalArgumentException()
                }


            }

            case StoreI(s) =>
            {
                assert(stack.length > 0)
                assert(env.contains(s))
                (env(s)::stack, env)
            }

            case PushI(f) => (f :: stack,env)

            case AddI => stack match
            {
                case i1 :: i2 :: tail =>
                    (i1 + i2 :: tail, env)
                case _ => throw new IllegalArgumentException()
            }
            //USE V1 and V2
            case SubI => stack match
            {
                case i1 :: i2 :: tail => (i1 - i2 :: tail, env)
                case _ => throw new IllegalArgumentException()

            }

            case MultI => stack match
            {
                case i1 :: i2 :: tail => (i1 * i2 :: tail, env)
                case _ => throw new IllegalArgumentException()
            }
            //USE V1 and V2
            case DivI => stack match
            {
                case i1 :: i2 :: tail => (i1 / i2 :: tail, env)
                case _ => throw new IllegalArgumentException()
            }

            case ExpI => stack match
            {
                case Nil => throw new IllegalArgumentException()
                case head :: tail => {
                    (scala.math.exp(head) :: tail,env)
                }
            }

            case LogI => stack match
            {
                case Nil => throw new IllegalArgumentException()
                case head :: tail =>
                {
                    if (head > 0)
                    {
                        (scala.math.log(head) :: tail,env)
                    }
                    else
                    {
                        throw new IllegalArgumentException()
                    }
                }
            }

            case SinI => stack match
            {
                case Nil => throw new IllegalArgumentException()
                case head :: tail =>
                {
                    (scala.math.sin(head) :: tail,env)
                }
            }

            case CosI => stack match
            {
                case Nil => throw new IllegalArgumentException()
                case head :: tail =>
                {
                    (scala.math.cos(head) :: tail,env)
                }
            }

            case PopI => stack match
            {
                case Nil => throw new IllegalArgumentException()
                case i1 :: tail =>
                {
                    (tail,env)
                }
            }
        }
    }

    /* Function emulateStackMachine
       Execute the list of instructions provided as inputs using the
       emulateSingleInstruction function.
       Use foldLeft over list of instruction rather than a for loop if you can.
       Return value must be the final environment.

       Hint: accumulator for foldLeft must be a tuple (List[Double], Map[String,Double])
             initial value of this accumulator must be (Nil, Map.empty)
             You should use emulateSingleInstruction to update the accmulator.
             It will all fit nicely once you figure it out.
     */
    def emulateStackMachine(instructionList: List[StackMachineInstruction]): Map[String, Double] =
    {
        val instList = instructionList.foldLeft[(List[Double], Map[String, Double])](Nil,Map.empty)((acc, SMI) =>
        {
            emulateSingleInstruction(acc._1, acc._2, SMI)
        })
        instList._2
    }
}