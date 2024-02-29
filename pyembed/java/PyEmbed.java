package pyembed;

public class PyEmbed {
    public native int addInPython(int a, int b);
    public native void transformArray(double[] output, double[] input);
}