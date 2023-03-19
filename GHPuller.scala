// Oto Brglez <otobrglez@gmail.com>
//> using scala "3.2"
//> using platform "native"
//> using lib "dev.zio::zio::2.0.10"
//> using lib "io.github.cquiroz::scala-java-time::2.5.0-M1"
//> using mainClass "GHPuller"

import zio._
import ZIO.{attempt, fromOption}
import zio.Console._
import Console.printLine
import scala.scalanative.unsafe._
import scala.scalanative.libc._
import CUtils.{fromCString, toCString}

@extern
@link("curl")
object CurlRequests { def get(str: CString): CString = extern }

final case class Response(body: String, headers: Map[String, String] = Map.empty)
object Requests:
  def get(url: String): Task[Response] =
    for
      rPointer <- attempt(Zone(z => CurlRequests.get(toCString(url)(z))))
      raw      <- attempt(fromCString(rPointer))
      response <- attempt("\\r\\n\\r\\n".r.split(raw))
      // Doing some header/body parsing here.
      headers  <- fromOption(response.headOption).map {
        _.split("\n")
          .drop(1)
          .map { row =>
            val k :: v :: xs = row.split(":").map(_.trim()).toList: @unchecked
            k -> (List(v) ++ xs).mkString(":")
          }
          .toMap
      }.orDieWith(_ => new RuntimeException("Failed reading headers."))
      body     <- fromOption(response.lastOption).orDieWith(_ => new RuntimeException("Failed reading body."))
    yield Response(body, headers)

object GHPuller extends ZIOAppDefault:
  def run =
    for
      ip <- Requests.get("http://icanhazip.com")
      _  <- printLine(s"Your IP is: ${ip.body}")
    yield ()
