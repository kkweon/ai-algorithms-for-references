main = (readLn :: IO Int) >>= \a -> putStrLn $ unlines $ take a . repeat $ "Hello Algospot!"
