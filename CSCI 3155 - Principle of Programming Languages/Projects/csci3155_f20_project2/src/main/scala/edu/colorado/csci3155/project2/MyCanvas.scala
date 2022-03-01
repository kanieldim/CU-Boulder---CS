package edu.colorado.csci3155.project2

/* A class to maintain a canvas. */
import java.awt.geom.{Ellipse2D, Rectangle2D}
import java.awt.{Graphics2D}

/* A figure is a sealed trait. It can be a Polygon or a "MyCircle"*/
sealed trait Figure {
    def getBoundingBox: (Double, Double, Double, Double)
    def translate(shiftX: Double, shiftY: Double): Figure

    def render(g: Graphics2D, scaleX: Double, scaleY: Double, shiftX: Double, shiftY: Double): Unit
}

/*
 Class Polygon
   A polygon is defined by a list of its vertices
 */

case class Polygon(val cList: List[(Double, Double)]) extends Figure {
    //TODO: Define the bounding box of the polygon
    override def getBoundingBox: (Double, Double, Double, Double ) =
    {
        cList.foldLeft( (Double.MaxValue, Double.MinValue, Double.MaxValue, Double.MinValue) )
        {
            case( (originalMin_x, originalMax_x, originalMin_y, originalMax_y), (x, y) ) =>
            {
                val newMin_x = if (x < originalMin_x ) x else originalMin_x
                val newMax_x = if (x > originalMax_x) x else originalMax_x
                val newMin_y = if (y < originalMin_x) y else originalMin_y
                val newMax_y = if (y > originalMax_y) y else originalMax_y

                (newMin_x, newMax_x, newMin_y, newMax_y)
            }
        }
    }
    //TODO: Create a new polygon by shifting each vertex in cList by (x,y)
    //    Do not change the order in which the vertices appear
    override def translate(shiftX: Double, shiftY: Double): Polygon =
    {
        new Polygon(cList.map{ case(x, y) => (shiftX + x, shiftY + y)})
    }

    // Function: render -- draw the polygon. Do not edit this function.
    override def render(g: Graphics2D, scaleX: Double, scaleY: Double, shiftX: Double, shiftY: Double) = {
        val xPoints: Array[Int] = new Array[Int](cList.length)
        val yPoints: Array[Int] = new Array[Int](cList.length)
        for (i <- 0 until cList.length){
            xPoints(i) = ((cList(i)._1 + shiftX )* scaleX).toInt
            yPoints(i) = ((cList(i)._2 + shiftY) * scaleY).toInt
        }
        g.drawPolygon(xPoints, yPoints, cList.length)
    }
}

/*
  Class MyCircle
  Define a circle with a given center c and radius r
 */
case class MyCircle(val c: (Double, Double), val r: Double) extends Figure {
    //TODO: Define the bounding box for the circle
    override def getBoundingBox: (Double, Double, Double, Double) =
    {
        val (x, y) = c
        val min_x = x - r
        val max_x = x + r
        val min_y = y - r
        val max_y = y + r

        (min_x, max_x, min_y, max_y)
    }


    //TODO: Create a new circle by shifting the center
    override def translate(shiftX: Double, shiftY: Double): MyCircle =
    {
        new MyCircle( (c._1 + shiftX, c._2 + shiftY), r)
    }

    // Function: render -- draw the polygon. Do not edit this function.
    override def render(g: Graphics2D, scaleX: Double, scaleY: Double, shiftX: Double, shiftY: Double) = {
        val centerX = ((c._1 + shiftX) * scaleX) .toInt
        val centerY = ((c._2 + shiftY) * scaleY) .toInt
        val radX = (r * scaleX).toInt
        val radY = (r * math.abs(scaleY)).toInt
        //g.draw(new Ellipse2D.Double(centerX, centerY, radX, radY))
        g.drawOval(centerX-radX, centerY-radY, 2*radX, 2*radY)
    }
}

/*
  Class : MyCanvas
  Define a canvas through a list of figure objects. Figure objects can be circles or polygons.
 */
class MyCanvas (val listOfObjects: List[Figure]) {
    // TODO: Write a function to get the boundingbox for the entire canvas.
    // Hint: use existing boundingbox functions defined in each figure.
    def getBoundingBox: (Double, Double, Double, Double) =
    {
        listOfObjects.foldLeft( (Double.MaxValue, Double.MinValue, Double.MaxValue, Double.MinValue))
        {
            case( (originalMin_x, originalMax_x, originalMin_y, originalMax_y), fig ) =>
            {
                val (figMin_x, figMax_x, figMin_y, figMax_y) = fig.getBoundingBox

                val newMin_x = if (figMin_x < originalMin_x ) figMin_x else originalMin_x
                val newMax_x = if (figMax_x > originalMax_x) figMax_x else originalMax_x
                val newMin_y = if (figMin_y < originalMin_x) figMin_y else originalMin_y
                val newMax_y = if (figMax_y > originalMax_y) figMax_y else originalMax_y

                (newMin_x, newMax_x, newMin_y, newMax_y)
            }
        }
    }

    //TODO: Write a function to translate each figure in the canvas by shiftX, shiftY
    def translate(shiftX: Double, shiftY: Double): MyCanvas =
    {
        new MyCanvas(listOfObjects.map{x => x.translate(shiftX, shiftY)})
    }



    //TODO: Write a function that will return a new MyCanvas object that places
    // all the objects in myc2 to the right of the objects in this MyCanvas.
    // refer to the notebook documentation on how to perform this.
    def placeRight(myc2: MyCanvas):MyCanvas =
    {
        val (min_x1, max_x1, min_y1, max_y1) = this.getBoundingBox
        val (min_x2, max_x2, min_y2, max_y2) = myc2.getBoundingBox

        val new_x = max_x1 - min_x1
        val new_y = (max_y1 - min_y1) / 2 - (max_y2 - min_y2) / 2

        val new_c = myc2.translate(new_x, new_y)

        this.overlap(new_c)
    }

    //TODO: Write a function that will return a new MyCanvas object that places
    // all the figures in myc2 on top of the figures in this MyCanvas.
    // refer to the notebook documentation on how to perform this.
    def placeTop(myc2: MyCanvas): MyCanvas =
    {
        val (min_x1, max_x1, min_y1, max_y1) = this.getBoundingBox
        val (min_x2, max_x2, min_y2, max_y2) = myc2.getBoundingBox

        val new_x = (max_x1 - min_x1) / 2 - (max_x2 - min_x2) / 2
        val new_y = max_y1 - min_y1

        val new_c = myc2.translate(new_x, new_y)

        this.overlap(new_c)
    }

    //TODO: Write a function that will rotate each figure in the canvas using
    // the angle `ang` defined in radians.
    // Suggestion: first write rotation functions for polygon and circle.
    //             those functions have not been added in the classes but you can do so with the
    //             appropriate signature.
    // rotating a polygon is simply rotating each vertex.
    // rotating a circle is simply rotating the center with radius unchanged.
    def rotate(angRad: Double): MyCanvas =
    {
        new MyCanvas( listOfObjects.map
        {
            case(Polygon(cList)) =>
            {
                val new_c_list = cList.map{ case(a, b) => (a * math.cos(angRad) - b * math.sin(angRad), a * math.sin(angRad) + b * math.cos(angRad)) }
                new Polygon( new_c_list )
            }
            case(MyCircle(c, r)) =>
            {
                val (a, b) = c
                val new_center = (a * math.cos(angRad) - b * math.sin(angRad), a * math.sin(angRad) + b * math.cos(angRad))
                new MyCircle(new_center, r)
            }

        })
    }

    // Function to draw the canvas. Do not edit.
    def render(g: Graphics2D, xMax: Double, yMax: Double) = {
        val (lx1, ux1, ly1, uy1) = this.getBoundingBox
        val shiftx = -lx1
        val shifty = -uy1
        val scaleX = xMax/(ux1 - lx1  + 1.0)
        val scaleY = yMax/(uy1 - ly1 + 1.0)
        listOfObjects.foreach(f => f.render(g,scaleX, -scaleY, shiftx, shifty))
    }

    def overlap(c2: MyCanvas): MyCanvas = {
        new MyCanvas(listOfObjects ++ c2.listOfObjects)
    }

    // DO NOT EDIT THE CODE BELOW
    override def toString: String = {
        listOfObjects.foldLeft[String] ("") { case (acc, fig) => acc ++ fig.toString }
    }
    // DO NOT EDIT
    def getListOfObjects: List[Figure] = listOfObjects

    // DO NOT EDIT
    def numPolygons: Int =
        listOfObjects.count {
            case Polygon(_) => true
            case _ => false }

    //DO NOT EDIT
    def numCircles: Int = {
        listOfObjects.count {
            case MyCircle(_,_) => true
            case _ => false }
    }
    //DO NOT EDIT
    def numVerticesTotal: Int = {
        listOfObjects.foldLeft[Int](0) ((acc, f) =>
            f match {
                case Polygon(lst1) => acc + lst1.length
                case _ => acc
            }
        )
    }
}
