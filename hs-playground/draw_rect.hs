import Control.Monad
import Data.Bits
import Data.Functor ((<$>))

toTuple :: [Int] -> (Int, Int)
toTuple (x : y : _) = (x, y)
tuTuple _ = error "List is empty"

readTuple :: IO (Int, Int)
readTuple = toTuple . map read . words <$> getLine

printTuple :: (Int, Int) -> IO ()
printTuple (a, b) = do
    putStr . show $ a
    putStr " "
    print b


main = do
    nTest <- readLn :: IO Int
    forM_ [1..nTest] (\_ -> do
        (a, b) <- readTuple
        (c, d) <- readTuple
        (e, f) <- readTuple
        printTuple (a `xor` c `xor` e, b `xor` d `xor` f))
