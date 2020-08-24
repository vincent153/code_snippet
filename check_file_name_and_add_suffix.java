public static String getNewFileName(File oldFile,int suffix){
    int index = oldFile.getAbsolutePath().lastIndexOf('.');
    String fileName = oldFile.getAbsolutePath().substring(0,index);
    String fileExtension =  oldFile.getAbsolutePath().substring(index);
    String newFilename = oldFile.getAbsolutePath();
    if(oldFile.exists()){
        File newFile = new File(fileName+"_"+suffix+fileExtension);
        if(newFile.exists()){
            Log.d(TAG,"getNewFileName::new file exists");
            return getNewFileName(oldFile,++suffix);
        }else{
            return newFile.getAbsolutePath();
        }
    }
    return newFilename;
}
