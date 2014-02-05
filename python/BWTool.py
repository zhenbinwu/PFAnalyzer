import os
import fnmatch

def GetList(path):
    matches = []
    filelist = []

    if os.path.isfile(path):
      matches.append(path)
    else:
      for root, dirnames, filenames in os.walk(path):
        for filename in fnmatch.filter(filenames, '*.root'):
          matches.append(os.path.join(root, filename))

    #matches.append(path)

    if "/eos/" in path or "/data" in path:
        for file in matches:
            print file
            filelist.append("file:%s" % file)

    if "pnfs" in path:
        for file in matches:
            #filelist.append("dcap://cmsdca1.fnal.gov:24139/pnfs/fnal.gov/usr/%s"
            filelist.append("dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/%s"
                            % file.split('/', 2)[-1])

    print filelist
    return filelist
