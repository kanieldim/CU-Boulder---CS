package edu.colorado.csci3155.project2

object Interpreter {

    def binaryExprEval(expr: Expr, expr1: Expr, env: Environment)(fun: (Value, Value) => Value): Value = {
        val v1 = evalExpr(expr, env)
        val v2 = evalExpr(expr1, env)
        fun(v1, v2)
    }

    def evalExpr(e: Expr, env: Environment): Value = e match {
        case Const(d) => NumValue(d)
        case ConstBool(b) => BoolValue(b)
        case Ident(s) => env.lookup(s)
        case Line(l) =>
        {
            val v = evalExpr(l, env)

            v match
            {
                case NumValue(d) =>
                {
                    val new_polygon = new Polygon( List( (0.0, 0.0), (d, 0.0) ) )
                    val new_canvas = new MyCanvas( List(new_polygon) )
                    FigValue(new_canvas)
                }
                case _ => throw new IllegalArgumentException("No line produced a NumValue")
            }

        } //TODO: Handle a line object

        case EquiTriangle(sideLength) =>
        {
            val v = evalExpr(sideLength, env)

            v match
            {
                case NumValue(d) =>
                {
                    val new_polygon = new Polygon( List( (0,0), (0,d), (d / 2, math.sqrt(3 * d) / 2) ) )
                    val new_canvas = new MyCanvas( List(new_polygon) )
                    FigValue(new_canvas)
                }
                case _ => throw new IllegalArgumentException("No EquTriangle produced a NumValue")
            }
        } // TODO: Handle Equilateral Triangle

        case Rectangle(sideLength) =>
        {
            val v = evalExpr(sideLength, env)

            v match
            {
                case NumValue(d) =>
                {
                    val new_polygon = new Polygon( List( (0, 0), (0, d), (d, d), (d, 0) ) )
                    val new_canvas = new MyCanvas( List(new_polygon) )
                    FigValue(new_canvas)
                }
                case _ => throw new IllegalArgumentException("No Rectangle produced a NumValue")
            }
        } // TODO: Handle square given the side length

        case Circle(rad) =>
        {
            val v = evalExpr(rad, env)

            v match
            {
                case NumValue(d) =>
                {
                    val new_circle = new MyCircle( (d, d), d)
                    val new_canvas = new MyCanvas( List(new_circle) )
                    FigValue(new_canvas)
                }
                case _ => throw new IllegalArgumentException("No Circle produced a NumValue")
            }
        } //TODO: Handle circle

        case Plus (e1, e2) =>
        {
            val v1 = evalExpr(e1, env)
            val v2 = evalExpr(e2, env)

            (v1, v2) match
            {
                case ( NumValue(b1), NumValue(b2) ) => NumValue(b1 + b2)

                case ( FigValue(b1), FigValue(b2) ) => FigValue(b1 overlap b2)

                case _ => throw new IllegalArgumentException("No Plus produced a NumValue or a FigValue")
            }

        } // TODO: Handle addition of numbers or figures
        case Minus (e1, e2) => binaryExprEval(e1, e2, env) (ValueOps.minus)
        case Mult(e1, e2) =>
        {
            val v1 = evalExpr(e1, env)
            val v2 = evalExpr(e2, env)

            (v1, v2) match
            {
                case ( NumValue(b1), NumValue(b2) ) =>
                    NumValue(b1 * b2)

                case ( FigValue(b1), FigValue(b2) ) =>
                    FigValue(b1 placeRight b2)

                case _ => throw new IllegalArgumentException("No Mult produced a NumValue or a FigValue")
            }
        } // TODO: Handle multiplication of numbers or figures
        case Div(e1, e2) =>
        {
            val v1 = evalExpr(e1, env)
            val v2 = evalExpr(e2, env)

            (v1, v2) match
            {
                case ( NumValue(b1), NumValue(b2) ) =>
                    NumValue(b1 / b2)

                case ( FigValue(b1), FigValue(b2) ) =>
                    FigValue(b1 placeTop b2)

                case ( FigValue(b1), NumValue(b2) ) =>
                    FigValue(b1 rotate b2)

                case _ => throw new IllegalArgumentException("No Div produced a NumValue or a FigValue")
            }
        } // TODO: Handle division

        case Geq(e1, e2) => binaryExprEval(e1, e2, env) (ValueOps.geq)
        case Gt(e1, e2) => binaryExprEval(e1, e2, env) (ValueOps.gt)
        case Eq(e1, e2) => binaryExprEval(e1, e2, env) (ValueOps.equal)
        case Neq(e1, e2) => binaryExprEval(e1, e2, env) (ValueOps.notEqual)
        case And(e1, e2) => {
            val v1 = evalExpr(e1, env)
            v1 match {
                case BoolValue(true) => {
                    val v2 = evalExpr(e2, env)
                    v2 match {
                        case BoolValue(_) => v2
                        case _ => throw new IllegalArgumentException("And applied to a non-Boolean value")
                    }
                }
                case BoolValue(false) => BoolValue(false)
                case _ => throw new IllegalArgumentException("And applied to a non-boolean value")
            }
        }

        case Or(e1, e2) => {
            val v1 = evalExpr(e1, env)
            v1 match {
                case BoolValue(true) => BoolValue(true)
                case BoolValue(false) => {
                    val v2 = evalExpr(e2, env)
                    v2 match {
                        case BoolValue(_) => v2
                        case _ => throw new IllegalArgumentException("Or Applied to a non-Boolean value")
                    }
                }
                case _ => throw new IllegalArgumentException("Or Applied to a non-Boolean Value")
            }
        }

        case Not(e) => {
            val v = evalExpr(e, env)
            v match {
                case BoolValue(b) => BoolValue(!b)
                case _ => throw new IllegalArgumentException("Not applied to a non-Boolean Value")
            }
        }

        case IfThenElse(e, e1, e2) => {
            val v = evalExpr(e, env)
            v match {
                case BoolValue(true) => evalExpr(e1, env)
                case BoolValue(false) => evalExpr(e2,env)
                case _ => throw new IllegalArgumentException("If then else condition is not a Boolean value")
            }
        }


        case Let(x, e1, e2) => {
            val v1 = evalExpr(e1, env)
            val env2 = Extend(x, v1, env)
            evalExpr(e2, env2)
        }

        case FunDef(x, e) =>
        {
            Closure(x, e, env)
        } //TODO: Handle function definitions

        case LetRec(f, x, e1, e2) =>
        {
            val v = ExtendREC(f, x, e1, env)
            evalExpr(e2, v)
        } // TODO: Handle recursive functions -- look at Environment.scala

        case FunCall(fCallExpr, arg) =>
        {
            val v = evalExpr(fCallExpr, env)
            v match
            {
                case Closure(x, newClosure, tempEnv) =>
                {
                    val v2 = evalExpr(arg, env)
                    val newEval = Extend(x, v2, tempEnv)

                    evalExpr(newClosure, newEval)
                }

                case _ => throw new IllegalArgumentException("No function calls exist")
            }
        } // TODO: Handle function calls

    }

    def evalProgram(p: Program): Value = p match {
        case TopLevel(e) => evalExpr(e, EmptyEnvironment)
    }

}
